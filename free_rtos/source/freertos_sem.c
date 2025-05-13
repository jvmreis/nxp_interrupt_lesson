/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* NXP/Freescale includes */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"
#include "peripherals.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define TASK_PRIO          (configMAX_PRIORITIES - 1)  // Set task priority to highest
#define CONSUMER_LINE_SIZE 3
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1      // Enable optimized task selection

// Binary semaphores for synchronization
SemaphoreHandle_t xSemaphore_producer;
SemaphoreHandle_t xSemaphore_consumer;

// GPIO definitions
#define BOARD_USER_DEBUG_GPIO GPIO1
#define BOARD_USER_SER_DEBUG_GPIO_PIN 19U
#define BOARD_USER_SER_DEBUG_GPIO_MASK (1u << BOARD_USER_SER_DEBUG_GPIO_PIN)
#define BOARD_USER_LED_GPIO_PIN_MASK (1u << BOARD_USER_LED_GPIO_PIN)
#define BOARD_USER_BUTTON_GPIO_PIN_MASK (1u << BOARD_USER_BUTTON_GPIO_PIN)

// GPT output compare interrupt flag (channel 3)
#define GPT_OC3_FLAG (1U << 2)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

// Declaration of tasks
static void producer_task(void *pvParameters);
static void consumer_task(void *pvParameters);

// Volatile global variables for optional debug
volatile bool g_InputSignal = false;
volatile uint32_t intial_millis = 0;
volatile uint32_t cycleCnt = 0;

// Variable used for context switch from ISR
BaseType_t xHigherPriorityTaskWoken = pdFALSE;

/*******************************************************************************
 * Interrupt Service Routines
 ******************************************************************************/

/*!
 * @brief GPT2 interrupt handler
 * Triggered when GPT2 compare match occurs.
 * This ISR clears the interrupt flag and gives a semaphore to signal a task.
 */
void GPT2_IRQHandler(void)
{
    GPT2->SR = GPT_OC3_FLAG;  // Clear GPT output compare interrupt flag
    xSemaphoreGiveFromISR(xSemaphore_consumer, &xHigherPriorityTaskWoken); // Signal the consumer task
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken); // Force context switch if necessary
    __DSB(); // Data Synchronization Barrier for memory operations
}

/*!
 * @brief GPIO external interrupt handler (for button press).
 * Called when GPIO5_IO00 detects a falling edge (button press).
 */
void GPIO5_Combined_0_15_IRQHandler(void)
{
    // Clear interrupt flag for the button pin
    GPIO_PortClearInterruptFlags(GPIO5, BOARD_USER_BUTTON_GPIO_PIN_MASK);

    // Signal the consumer task through semaphore
    xSemaphoreGiveFromISR(xSemaphore_consumer, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    __DSB(); // Ensure all memory operations complete
}

/*******************************************************************************
 * Main Code
 ******************************************************************************/

/*!
 * @brief Main function - entry point of the application.
 */
int main(void)
{
    // Create binary semaphore for synchronization
    xSemaphore_consumer = xSemaphoreCreateBinary();
    if (xSemaphore_consumer == NULL)
    {
        PRINTF("xSemaphore_consumer creation failed.\r\n");
        vTaskSuspend(NULL); // Stop execution if semaphore creation fails
    }

    // Initialize board, peripherals, and debug console
    BOARD_InitHardware();
    BOARD_InitBootPeripherals();
    PRINTF("Hello World\r\n");

    // Enable cycle counter for debugging (DWT)
    CoreDebug->DEMCR |= 0x01000000;
    DWT->CTRL |= 0x00000001;

    // Configure LED as digital output
    gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};
    GPIO_PinInit(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, &led_config);

    // Enable interrupt for the user button (on GPIO5)
    GPIO_PortEnableInterrupts(GPIO5, 1U << BOARD_USER_BUTTON_GPIO_PIN);

    // Create the producer task
    if (xTaskCreate(producer_task, "PRODUCER_TASK", configMINIMAL_STACK_SIZE + 128, NULL, TASK_PRIO, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1); // Infinite loop if task creation fails
    }

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // If the scheduler returns (should not happen), enter infinite loop
    for (;;);
}

/*!
 * @brief Producer task
 * This task waits for a semaphore and generates a short debug pulse on GPIO when triggered.
 */
static void producer_task(void *pvParameters)
{
    while (1)
    {
        // Block indefinitely until the semaphore is given
        if (xSemaphoreTake(xSemaphore_consumer, portMAX_DELAY) == pdTRUE)
        {
            // Generate 3 quick writes to simulate a debug pulse
            GPIO1->DR = BOARD_USER_SER_DEBUG_GPIO_MASK;
            GPIO1->DR = BOARD_USER_SER_DEBUG_GPIO_MASK;
            GPIO1->DR = BOARD_USER_SER_DEBUG_GPIO_MASK;
            GPIO1->DR = 0;

            // Optional debug:
            // intial_millis = intial_millis - (SysTick->VAL);
            // GPIO_PortToggle(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN_MASK);
            // DWT->CYCCNT = 0;
            // PRINTF("xSemaphore take %d:%d\r\n", cycleCnt, intial_millis);
        }
    }
}

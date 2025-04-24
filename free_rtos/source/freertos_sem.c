/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"

#include "peripherals.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TASK_PRIO          (configMAX_PRIORITIES - 1)
#define CONSUMER_LINE_SIZE 3
SemaphoreHandle_t xSemaphore_producer;
SemaphoreHandle_t xSemaphore_consumer;

#define BOARD_USER_DEBUG_GPIO GPIO1
#define BOARD_USER_SER_DEBUG_GPIO_PIN 19U

#define BOARD_USER_SER_DEBUG_GPIO_MASK 1u << BOARD_USER_SER_DEBUG_GPIO_PIN

#define BOARD_USER_LED_GPIO_PIN_MASK 1u << BOARD_USER_LED_GPIO_PIN

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void producer_task(void *pvParameters);
static void consumer_task(void *pvParameters);

volatile bool g_InputSignal = false;
uint32_t intial_millis=0;


void BOARD_INITPINS_USER_BUTTON_callback(void *param)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;


    /* Producer is ready to provide item. */
    xSemaphoreGiveFromISR(xSemaphore_consumer,&xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	DWT->CYCCNT = 0;
	intial_millis = SysTick->VAL;

    /* clear the interrupt status */
    GPIO_PortClearInterruptFlags(BOARD_USER_BUTTON_GPIO, 1U << BOARD_USER_BUTTON_GPIO_PIN);

    SDK_ISR_EXIT_BARRIER;
}

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitHardware();
    BOARD_InitBootPeripherals();
    PRINTF("Hello World\r\n");

    CoreDebug->DEMCR |= 0x01000000;
    DWT->CTRL |= 0x00000001;


    xSemaphore_consumer = xSemaphoreCreateBinary();
    if (xSemaphore_consumer == NULL)
    {
        PRINTF("xSemaphore_consumer creation failed.\r\n");
        vTaskSuspend(NULL);
    }


    gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};


    GPIO_PinInit(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, &led_config);
    GPIO_PortEnableInterrupts(GPIO5, 1U << BOARD_USER_BUTTON_GPIO_PIN); // Se for GPIO5

    if (xTaskCreate(producer_task, "PRODUCER_TASK", configMINIMAL_STACK_SIZE + 128, NULL, TASK_PRIO, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }
    /* Start scheduling. */
    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task producer_task.
 */
static void producer_task(void *pvParameters)
{
    uint32_t i;

    while (1)
    {

        /* Producer is waiting when consumer will be ready to accept item. */
        if (xSemaphoreTake(xSemaphore_consumer, portMAX_DELAY) == pdTRUE)
        {
        	uint32_t cycleCnt = DWT->CYCCNT;
        	intial_millis = intial_millis - (SysTick->VAL);

            GPIO_PortToggle(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN_MASK);

            GPIO_PortToggle(BOARD_USER_DEBUG_GPIO, BOARD_USER_SER_DEBUG_GPIO_MASK);


            PRINTF("xSemaphore take %d:%d\r\n",cycleCnt,intial_millis);

        }
        else
        {
            PRINTF("xSemaphore waiting int.\r\n");
        }
    }
}



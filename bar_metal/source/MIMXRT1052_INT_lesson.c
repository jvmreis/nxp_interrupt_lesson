/*
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    MIMXRT1052_INT_lesson.c
 * @brief   Application entry point for demonstrating GPIO and GPT interrupt handling on RT1052.
 */

#include <stdio.h>
#include "board.h"                  // Board initialization utilities
#include "peripherals.h"           // Peripheral configuration (GPT, GPIO, etc.)
#include "pin_mux.h"               // Pin multiplexing setup
#include "clock_config.h"          // System clock initialization
#include "fsl_debug_console.h"     // Debug console for printf/logging
#include "fsl_adapter_gpio.h"      // HAL GPIO abstraction
#include "fsl_adapter_timer.h"     // HAL Timer abstraction

// Global flag used to indicate input signal (not actively used here)
volatile bool g_InputSignal = false;

// Variables for debugging/measurement (not used in current logic)
uint32_t intial_millis = 0;
uint32_t cycleCnt = 0;

// Define GPIO pins and bitmasks
#define BOARD_USER_DEBUG_GPIO GPIO1
#define BOARD_USER_SER_DEBUG_GPIO_PIN 19U
#define BOARD_USER_SER_DEBUG_GPIO_MASK (1u << BOARD_USER_SER_DEBUG_GPIO_PIN)

#define BOARD_USER_LED_GPIO_PIN_MASK (1u << BOARD_USER_LED_GPIO_PIN)
#define BOARD_USER_BUTTON_GPIO_PIN_MASK (1U << BOARD_USER_BUTTON_GPIO_PIN)

// GPT output compare channel 3 interrupt flag
#define GPT_OC3_FLAG (1U << 2)

/*!
 * @brief GPT2 IRQ handler
 * This is triggered when GPT2 Output Compare channel 3 matches.
 */
void GPT2_IRQHandler(void)
{
    // Generate a short pulse for oscilloscope debug by writing to GPIO directly
    GPIO1->DR = BOARD_USER_SER_DEBUG_GPIO_MASK;
    GPIO1->DR = 0;

    // Clear the GPT2 Output Compare Channel 3 interrupt flag
    GPT2->SR = GPT_OC3_FLAG;

    //g_InputSignal = true;

    // Ensure memory operations complete before leaving the ISR
    __DSB();
}

/*!
 * @brief GPIO external interrupt handler (hardware interrupt from a button).
 * Only used when ISR_GPIO_HAL_COMPARATION == 0.
 */
#if (ISR_GPIO_HAL_COMPARATION == 0U)
void GPIO5_Combined_0_15_IRQHandler(void)
{
    // Generate a short debug pulse on GPIO
    GPIO1->DR = BOARD_USER_SER_DEBUG_GPIO_MASK;
    GPIO1->DR = 0;

    // Clear GPIO interrupt flag for the user button pin
    GPIO_PortClearInterruptFlags(BOARD_USER_BUTTON_GPIO, BOARD_USER_BUTTON_GPIO_PIN_MASK);

    //g_InputSignal = true;

    __DSB(); // Ensure memory sync
}
#endif

/*!
 * @brief Software callback for the button using HAL interrupt service.
 * Only used when ISR_GPIO_HAL_COMPARATION > 0.
 */
void BOARD_INITPINS_USER_BUTTON_callback(void *param)
{
#if (ISR_GPIO_HAL_COMPARATION > 0U)
    // Generate pulse on debug GPIO
    GPIO1->DR = BOARD_USER_SER_DEBUG_GPIO_MASK;
    GPIO1->DR = 0;
#endif
}

/*!
 * @brief Main application entry point
 */
int main(void)
{
    // Initialize core peripherals and board
    BOARD_ConfigMPU();                 // Configure Memory Protection Unit
    BOARD_InitBootPins();             // Initialize pins defined in MCUXpresso Config Tools
    BOARD_InitBootClocks();           // Setup clock tree
    BOARD_InitBootPeripherals();      // Setup GPT, GPIO, etc.
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();         // Init UART debug console for printf
#endif

    PRINTF("Hello World\r\n");

    // Main loop
    while (1)
    {
        // If an input signal is detected (not used actively in this example)
        if (g_InputSignal)
        {
            // Debug example (SysTick usage not fully configured)
            intial_millis = intial_millis - (SysTick->VAL);
            PRINTF("Interruption working %d:%d\r\n", cycleCnt, intial_millis);

            // Toggle LED to indicate activity
            GPIO_PortToggle(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN_MASK);

            g_InputSignal = false;
        }
    }
}

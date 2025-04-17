/*
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    MIMXRT1052_INT_lesson.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "fsl_adapter_gpio.h"

/* TODO: insert other include files here. */
static void delay(void);
volatile bool g_InputSignal = false;
uint32_t intial_millis=0;

/*!
 * @brief Interrupt service fuction of switch.
 */
void BOARD_INITPINS_USER_BUTTON_callback(void *param)
{
    /* clear the interrupt status */
    GPIO_PortClearInterruptFlags(BOARD_USER_BUTTON_GPIO, 1U << BOARD_USER_BUTTON_GPIO_PIN);
    /* Change state of switch. */

     //intial_millis = SysTick->VAL;

    g_InputSignal = true;
    SDK_ISR_EXIT_BARRIER;
}

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void)
{

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\r\n");

    gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

    GPIO_PinInit(BOARD_USER_LED_GPIO, BOARD_USER_LED_GPIO_PIN, &led_config);
    GPIO_PortEnableInterrupts(GPIO5, 1U << BOARD_USER_BUTTON_GPIO_PIN); // Se for GPIO5

    while (1)
    {
        if (g_InputSignal)
        {
            PRINTF("Interruption working \r\n");
            g_InputSignal = false;
        }
        SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        GPIO_PortToggle(BOARD_USER_LED_GPIO, 1u << BOARD_USER_LED_GPIO_PIN);
    }
}

static void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 1000000; ++i)
    {
        __NOP(); /* delay */
    }
}

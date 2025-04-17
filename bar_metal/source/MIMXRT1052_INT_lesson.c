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
volatile bool g_InputSignal = false;
uint32_t intial_millis=0;
uint32_t cycleCnt=0;
#define BOARD_USER_DEBUG_GPIO GPIO1
#define BOARD_USER_SER_DEBUG_GPIO_PIN 19U

/*!
 * @brief Interrupt service fuction of switch.
 */
void BOARD_INITPINS_USER_BUTTON_callback(void *param)
{

	GPIO_PinWrite(BOARD_USER_DEBUG_GPIO, BOARD_USER_SER_DEBUG_GPIO_PIN,1);
//  GPIO_PortToggle(BOARD_USER_DEBUG_GPIO, 1u << BOARD_USER_SER_DEBUG_GPIO_PIN);
//	GPIO_PinWrite(BOARD_USER_DEBUG_GPIO, BOARD_USER_SER_DEBUG_GPIO_PIN,0);

    GPIO_PortToggle(BOARD_USER_LED_GPIO, 1u << BOARD_USER_LED_GPIO_PIN);

	intial_millis = SysTick->VAL;

    /* clear the interrupt status */
    g_InputSignal = true;

	DWT->CYCCNT = 0;
    SDK_ISR_EXIT_BARRIER;
    cycleCnt= DWT->CYCCNT;

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

    while (1)
    {
        if (g_InputSignal)
        {
        	intial_millis = intial_millis - (SysTick->VAL);
            PRINTF("Interruption working %d:%d\r\n",cycleCnt,intial_millis);
        	GPIO_PinWrite(BOARD_USER_DEBUG_GPIO, BOARD_USER_SER_DEBUG_GPIO_PIN,0);

            g_InputSignal = false;
        }
    }
}


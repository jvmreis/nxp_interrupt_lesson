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

#include "fsl_adapter_timer.h"

/* TODO: insert other include files here. */
volatile bool g_InputSignal = false;
uint32_t intial_millis=0;
uint32_t cycleCnt=0;
#define BOARD_USER_DEBUG_GPIO GPIO1
#define BOARD_USER_SER_DEBUG_GPIO_PIN 19U


///* GPT2_IRQn interrupt handler */
//void GPT2_IRQHandler(void) {
//  /*  Place your code here */
//    GPIO_PortToggle(BOARD_USER_LED_GPIO, 1u << BOARD_USER_LED_GPIO_PIN);
//
//  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
//     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
//  #if defined __CORTEX_M && (__CORTEX_M == 4U)
//    __DSB();
//  #endif
//}

void GPT2_Callback(void *param)
{
    GPIO_PortToggle(BOARD_USER_LED_GPIO, 1u << BOARD_USER_LED_GPIO_PIN);

    // Seu código de callback aqui
}
TIMER_HANDLE_DEFINE(gptTimerHandle);

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

    // Configuração do Timer HAL (GPT2 para 1 Hz)
    hal_timer_config_t timerConfig;
    timerConfig.timeout = 1000000U;       // 1000000 us = 1 s intervalo
    timerConfig.srcClock_Hz = 75000000U;  // clock do GPT2 em Hz (75 MHz)
    timerConfig.instance = 2;             // utilizar GPT2 (instância 2)
    HAL_TimerInit((hal_timer_handle_t)gptTimerHandle, &timerConfig);

    // Registra callback e inicia o timer
    HAL_TimerInstallCallback((hal_timer_handle_t)gptTimerHandle, GPT2_Callback, NULL);
    HAL_TimerEnable((hal_timer_handle_t)gptTimerHandle);

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


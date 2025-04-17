/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v17.0
processor: MIMXRT1052xxxxB
package_id: MIMXRT1052DVL6B
mcu_data: ksdk2_0
processor_version: 24.12.10
board: IMXRT1050-EVKB
pin_labels:
- {pin_num: F14, pin_signal: GPIO_AD_B0_09, label: LED_1, identifier: USER_led}
- {pin_num: L6, pin_signal: WAKEUP, label: GPIO_int, identifier: USER_BUTTON}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: L14, peripheral: LPUART1, signal: RX, pin_signal: GPIO_AD_B0_13, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Down_100K_Ohm,
    pull_keeper_select: Keeper, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_100, drive_strength: R0_6, slew_rate: Slow}
  - {pin_num: K14, peripheral: LPUART1, signal: TX, pin_signal: GPIO_AD_B0_12, software_input_on: Disable, hysteresis_enable: Disable, pull_up_down_config: Pull_Down_100K_Ohm,
    pull_keeper_select: Keeper, pull_keeper_enable: Enable, open_drain: Disable, speed: MHZ_100, drive_strength: R0_6, slew_rate: Slow}
  - {pin_num: F14, peripheral: GPIO1, signal: 'gpio_io, 09', pin_signal: GPIO_AD_B0_09, direction: OUTPUT}
  - {pin_num: L6, peripheral: GPIO5, signal: 'gpio_io, 00', pin_signal: WAKEUP, direction: INPUT, gpio_interrupt: kGPIO_IntFallingEdge}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           
  CLOCK_EnableClock(kCLOCK_IomuxcSnvs);       

  /* GPIO configuration of USER_led on GPIO_AD_B0_09 (pin F14) */
  gpio_pin_config_t USER_led_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_B0_09 (pin F14) */
  GPIO_PinInit(GPIO1, 9U, &USER_led_config);

  /* GPIO configuration of USER_BUTTON on WAKEUP (pin L6) */
  gpio_pin_config_t USER_BUTTON_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_IntFallingEdge
  };
  /* Initialize GPIO functionality on WAKEUP (pin L6) */
  GPIO_PinInit(GPIO5, 0U, &USER_BUTTON_config);
  /* Enable GPIO pin interrupt on WAKEUP (pin L6) */
  GPIO_PortEnableInterrupts(GPIO5, 1U << 0U);

  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, 0U); 
#if FSL_IOMUXC_DRIVER_VERSION >= MAKE_VERSION(2, 0, 3)
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPUART1_TXD, 0U); 
#else
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPUART1_TX, 0U); 
#endif
#if FSL_IOMUXC_DRIVER_VERSION >= MAKE_VERSION(2, 0, 3)
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPUART1_RXD, 0U); 
#else
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPUART1_RX, 0U); 
#endif
  IOMUXC_SetPinMux(IOMUXC_SNVS_WAKEUP_GPIO5_IO00, 0U); 
#if FSL_IOMUXC_DRIVER_VERSION >= MAKE_VERSION(2, 0, 3)
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_12_LPUART1_TXD, 0x10B0U); 
#else
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_12_LPUART1_TX, 0x10B0U); 
#endif
#if FSL_IOMUXC_DRIVER_VERSION >= MAKE_VERSION(2, 0, 3)
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_13_LPUART1_RXD, 0x10B0U); 
#else
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_13_LPUART1_RX, 0x10B0U); 
#endif
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

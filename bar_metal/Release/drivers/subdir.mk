################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dcdc.c \
../drivers/fsl_gpc.c \
../drivers/fsl_gpio.c \
../drivers/fsl_gpt.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_pmu.c \
../drivers/fsl_src.c 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dcdc.d \
./drivers/fsl_gpc.d \
./drivers/fsl_gpio.d \
./drivers/fsl_gpt.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_pmu.d \
./drivers/fsl_src.d 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dcdc.o \
./drivers/fsl_gpc.o \
./drivers/fsl_gpio.o \
./drivers/fsl_gpt.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_pmu.o \
./drivers/fsl_src.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"C:\Github\nxp_interrupt_lesson\bar_metal\drivers" -I"C:\Github\nxp_interrupt_lesson\bar_metal\component\uart" -I"C:\Github\nxp_interrupt_lesson\bar_metal\xip" -I"C:\Github\nxp_interrupt_lesson\bar_metal\utilities\str" -I"C:\Github\nxp_interrupt_lesson\bar_metal\CMSIS" -I"C:\Github\nxp_interrupt_lesson\bar_metal\CMSIS\m-profile" -I"C:\Github\nxp_interrupt_lesson\bar_metal\utilities" -I"C:\Github\nxp_interrupt_lesson\bar_metal\device" -I"C:\Github\nxp_interrupt_lesson\bar_metal\device\periph" -I"C:\Github\nxp_interrupt_lesson\bar_metal\utilities\debug_console_lite" -I"C:\Github\nxp_interrupt_lesson\bar_metal\component\gpio" -I"C:\Github\nxp_interrupt_lesson\bar_metal\board" -I"C:\Github\nxp_interrupt_lesson\bar_metal\source" -Os -fno-common -g -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dcdc.d ./drivers/fsl_dcdc.o ./drivers/fsl_gpc.d ./drivers/fsl_gpc.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_gpt.d ./drivers/fsl_gpt.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_pmu.d ./drivers/fsl_pmu.o ./drivers/fsl_src.d ./drivers/fsl_src.o

.PHONY: clean-drivers


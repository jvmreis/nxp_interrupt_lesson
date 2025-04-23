################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_MIMXRT1052.c 

C_DEPS += \
./device/system_MIMXRT1052.d 

OBJS += \
./device/system_MIMXRT1052.o 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DTIMER_PORT_TYPE_GPT=1 -I"C:\Github\nxp_interrupt_lesson\bar_metal\drivers" -I"C:\Github\nxp_interrupt_lesson\bar_metal\component\uart" -I"C:\Github\nxp_interrupt_lesson\bar_metal\xip" -I"C:\Github\nxp_interrupt_lesson\bar_metal\utilities\str" -I"C:\Github\nxp_interrupt_lesson\bar_metal\CMSIS" -I"C:\Github\nxp_interrupt_lesson\bar_metal\CMSIS\m-profile" -I"C:\Github\nxp_interrupt_lesson\bar_metal\utilities" -I"C:\Github\nxp_interrupt_lesson\bar_metal\device" -I"C:\Github\nxp_interrupt_lesson\bar_metal\device\periph" -I"C:\Github\nxp_interrupt_lesson\bar_metal\utilities\debug_console_lite" -I"C:\Github\nxp_interrupt_lesson\bar_metal\component\gpio" -I"C:\Github\nxp_interrupt_lesson\bar_metal\component\timer" -I"C:\Github\nxp_interrupt_lesson\bar_metal\board" -I"C:\Github\nxp_interrupt_lesson\bar_metal\source" -Os -fno-common -g -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-device

clean-device:
	-$(RM) ./device/system_MIMXRT1052.d ./device/system_MIMXRT1052.o

.PHONY: clean-device


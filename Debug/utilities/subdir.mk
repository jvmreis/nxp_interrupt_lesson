################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c 

C_DEPS += \
./utilities/fsl_assert.d 

OBJS += \
./utilities/fsl_assert.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Github\nxp_interrupt_lesson\drivers" -I"C:\Github\nxp_interrupt_lesson\component\uart" -I"C:\Github\nxp_interrupt_lesson\xip" -I"C:\Github\nxp_interrupt_lesson\utilities\str" -I"C:\Github\nxp_interrupt_lesson\CMSIS" -I"C:\Github\nxp_interrupt_lesson\CMSIS\m-profile" -I"C:\Github\nxp_interrupt_lesson\utilities" -I"C:\Github\nxp_interrupt_lesson\device" -I"C:\Github\nxp_interrupt_lesson\device\periph" -I"C:\Github\nxp_interrupt_lesson\utilities\debug_console_lite" -I"C:\Github\nxp_interrupt_lesson\component\gpio" -I"C:\Github\nxp_interrupt_lesson\board" -I"C:\Github\nxp_interrupt_lesson\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o

.PHONY: clean-utilities


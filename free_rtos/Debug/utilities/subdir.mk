################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c 

S_UPPER_SRCS += \
../utilities/fsl_memcpy.S 

C_DEPS += \
./utilities/fsl_assert.d 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_memcpy.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DMCUXPRESSO_SDK -DXIP_BOOT_HEADER_ENABLE=1 -DXIP_EXTERNAL_FLASH=1 -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DSDK_OS_FREE_RTOS -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Github\nxp_interrupt_lesson\free_rtos\xip" -I"C:\Github\nxp_interrupt_lesson\free_rtos\drivers" -I"C:\Github\nxp_interrupt_lesson\free_rtos\CMSIS" -I"C:\Github\nxp_interrupt_lesson\free_rtos\CMSIS\m-profile" -I"C:\Github\nxp_interrupt_lesson\free_rtos\device" -I"C:\Github\nxp_interrupt_lesson\free_rtos\device\periph" -I"C:\Github\nxp_interrupt_lesson\free_rtos\utilities" -I"C:\Github\nxp_interrupt_lesson\free_rtos\utilities\str" -I"C:\Github\nxp_interrupt_lesson\free_rtos\utilities\debug_console_lite" -I"C:\Github\nxp_interrupt_lesson\free_rtos\component\uart" -I"C:\Github\nxp_interrupt_lesson\free_rtos\freertos\freertos-kernel\include" -I"C:\Github\nxp_interrupt_lesson\free_rtos\freertos\freertos-kernel\portable\GCC\ARM_CM4F" -I"C:\Github\nxp_interrupt_lesson\free_rtos\component\gpio" -I"C:\Github\nxp_interrupt_lesson\free_rtos\freertos\freertos-kernel\template" -I"C:\Github\nxp_interrupt_lesson\free_rtos\freertos\freertos-kernel\template\ARM_CM4F_4_priority_bits" -I"C:\Github\nxp_interrupt_lesson\free_rtos\source" -I"C:\Github\nxp_interrupt_lesson\free_rtos\board" -O0 -fno-common -g3 -gdwarf-4 -mthumb -c -ffunction-sections -fdata-sections -fno-builtin -imacros "C:\Github\nxp_interrupt_lesson\free_rtos\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

utilities/%.o: ../utilities/%.S utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -I"C:\Github\nxp_interrupt_lesson\free_rtos\xip" -I"C:\Github\nxp_interrupt_lesson\free_rtos\drivers" -I"C:\Github\nxp_interrupt_lesson\free_rtos\CMSIS" -I"C:\Github\nxp_interrupt_lesson\free_rtos\CMSIS\m-profile" -I"C:\Github\nxp_interrupt_lesson\free_rtos\device" -I"C:\Github\nxp_interrupt_lesson\free_rtos\device\periph" -I"C:\Github\nxp_interrupt_lesson\free_rtos\utilities" -I"C:\Github\nxp_interrupt_lesson\free_rtos\utilities\str" -I"C:\Github\nxp_interrupt_lesson\free_rtos\utilities\debug_console_lite" -I"C:\Github\nxp_interrupt_lesson\free_rtos\component\uart" -I"C:\Github\nxp_interrupt_lesson\free_rtos\freertos\freertos-kernel\include" -I"C:\Github\nxp_interrupt_lesson\free_rtos\freertos\freertos-kernel\portable\GCC\ARM_CM4F" -I"C:\Github\nxp_interrupt_lesson\free_rtos\component\gpio" -I"C:\Github\nxp_interrupt_lesson\free_rtos\freertos\freertos-kernel\template" -I"C:\Github\nxp_interrupt_lesson\free_rtos\freertos\freertos-kernel\template\ARM_CM4F_4_priority_bits" -I"C:\Github\nxp_interrupt_lesson\free_rtos\source" -g3 -gdwarf-4 -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o ./utilities/fsl_memcpy.o

.PHONY: clean-utilities


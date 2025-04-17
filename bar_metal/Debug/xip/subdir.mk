################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xip/dcd.c \
../xip/evkbimxrt1050_flexspi_nor_config.c \
../xip/fsl_flexspi_nor_boot.c 

C_DEPS += \
./xip/dcd.d \
./xip/evkbimxrt1050_flexspi_nor_config.d \
./xip/fsl_flexspi_nor_boot.d 

OBJS += \
./xip/dcd.o \
./xip/evkbimxrt1050_flexspi_nor_config.o \
./xip/fsl_flexspi_nor_boot.o 


# Each subdirectory must supply rules for building sources it contributes
xip/%.o: ../xip/%.c xip/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DMCUXPRESSO_SDK -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Github\nxp_interrupt_lesson\bar_metal\drivers" -I"C:\Github\nxp_interrupt_lesson\bar_metal\component\uart" -I"C:\Github\nxp_interrupt_lesson\bar_metal\xip" -I"C:\Github\nxp_interrupt_lesson\bar_metal\utilities\str" -I"C:\Github\nxp_interrupt_lesson\bar_metal\CMSIS" -I"C:\Github\nxp_interrupt_lesson\bar_metal\CMSIS\m-profile" -I"C:\Github\nxp_interrupt_lesson\bar_metal\utilities" -I"C:\Github\nxp_interrupt_lesson\bar_metal\device" -I"C:\Github\nxp_interrupt_lesson\bar_metal\device\periph" -I"C:\Github\nxp_interrupt_lesson\bar_metal\utilities\debug_console_lite" -I"C:\Github\nxp_interrupt_lesson\bar_metal\component\gpio" -I"C:\Github\nxp_interrupt_lesson\bar_metal\board" -I"C:\Github\nxp_interrupt_lesson\bar_metal\source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-xip

clean-xip:
	-$(RM) ./xip/dcd.d ./xip/dcd.o ./xip/evkbimxrt1050_flexspi_nor_config.d ./xip/evkbimxrt1050_flexspi_nor_config.o ./xip/fsl_flexspi_nor_boot.d ./xip/fsl_flexspi_nor_boot.o

.PHONY: clean-xip


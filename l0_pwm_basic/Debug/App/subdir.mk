################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/App.c \
../App/lcd_user.c 

OBJS += \
./App/App.o \
./App/lcd_user.o 

C_DEPS += \
./App/App.d \
./App/lcd_user.d 


# Each subdirectory must supply rules for building sources it contributes
App/App.o: ../App/App.c App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L052xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I../App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"App/App.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
App/lcd_user.o: ../App/lcd_user.c App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L052xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I../App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"App/lcd_user.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


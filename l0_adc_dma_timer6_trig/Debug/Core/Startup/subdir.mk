################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32l052k6tx.s 

OBJS += \
./Core/Startup/startup_stm32l052k6tx.o 

S_DEPS += \
./Core/Startup/startup_stm32l052k6tx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32l052k6tx.o: ../Core/Startup/startup_stm32l052k6tx.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -c -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32l052k6tx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"


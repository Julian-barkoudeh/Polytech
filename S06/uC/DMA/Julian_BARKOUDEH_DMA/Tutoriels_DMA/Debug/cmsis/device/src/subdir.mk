################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../cmsis/device/src/startup_stm32f072xb.s 

C_SRCS += \
../cmsis/device/src/system_stm32f0xx.c 

OBJS += \
./cmsis/device/src/startup_stm32f072xb.o \
./cmsis/device/src/system_stm32f0xx.o 

S_DEPS += \
./cmsis/device/src/startup_stm32f072xb.d 

C_DEPS += \
./cmsis/device/src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
cmsis/device/src/startup_stm32f072xb.o: ../cmsis/device/src/startup_stm32f072xb.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -c -x assembler-with-cpp -MMD -MP -MF"cmsis/device/src/startup_stm32f072xb.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
cmsis/device/src/system_stm32f0xx.o: ../cmsis/device/src/system_stm32f0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DSTM32F072RBHx -DDEBUG -c -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/cmsis/core" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/bsp/inc" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/cmsis/device/inc" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/app/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"cmsis/device/src/system_stm32f0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


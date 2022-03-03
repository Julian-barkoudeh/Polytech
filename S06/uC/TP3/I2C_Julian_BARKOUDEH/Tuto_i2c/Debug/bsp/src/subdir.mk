################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/src/bsp.c \
../bsp/src/delay.c 

OBJS += \
./bsp/src/bsp.o \
./bsp/src/delay.o 

C_DEPS += \
./bsp/src/bsp.d \
./bsp/src/delay.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/src/bsp.o: ../bsp/src/bsp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DSTM32F072RBHx -DDEBUG -c -I"D:/Microcontrolleur/Workplace_1/Tuto_i2c/cmsis/core" -I"D:/Microcontrolleur/Workplace_1/Tuto_i2c/bsp/inc" -I"D:/Microcontrolleur/Workplace_1/Tuto_i2c/cmsis/device/inc" -I"D:/Microcontrolleur/Workplace_1/Tuto_i2c/app/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"bsp/src/bsp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
bsp/src/delay.o: ../bsp/src/delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DSTM32F072RBHx -DDEBUG -c -I"D:/Microcontrolleur/Workplace_1/Tuto_i2c/cmsis/core" -I"D:/Microcontrolleur/Workplace_1/Tuto_i2c/bsp/inc" -I"D:/Microcontrolleur/Workplace_1/Tuto_i2c/cmsis/device/inc" -I"D:/Microcontrolleur/Workplace_1/Tuto_i2c/app/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"bsp/src/delay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


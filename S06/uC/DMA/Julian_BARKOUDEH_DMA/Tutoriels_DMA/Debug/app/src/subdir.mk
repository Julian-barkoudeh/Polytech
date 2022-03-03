################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/src/main.c \
../app/src/printf-stdarg.c \
../app/src/stm32f0xx_it.c 

OBJS += \
./app/src/main.o \
./app/src/printf-stdarg.o \
./app/src/stm32f0xx_it.o 

C_DEPS += \
./app/src/main.d \
./app/src/printf-stdarg.d \
./app/src/stm32f0xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
app/src/main.o: ../app/src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DSTM32F072RBHx -DDEBUG -c -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/cmsis/core" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/bsp/inc" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/cmsis/device/inc" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/app/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"app/src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
app/src/printf-stdarg.o: ../app/src/printf-stdarg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DSTM32F072RBHx -DDEBUG -c -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/cmsis/core" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/bsp/inc" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/cmsis/device/inc" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/app/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"app/src/printf-stdarg.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
app/src/stm32f0xx_it.o: ../app/src/stm32f0xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32 -DSTM32F0 -DSTM32F072RBHx -DDEBUG -c -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/cmsis/core" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/bsp/inc" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/cmsis/device/inc" -I"D:/Microcontrolleur/Workplace_1/Tutoriels_DMA/app/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"app/src/stm32f0xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


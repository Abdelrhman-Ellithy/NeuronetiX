################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/GPIO_program.c \
../Src/MCAL/RCC_program.c 

OBJS += \
./Src/MCAL/GPIO_program.o \
./Src/MCAL/RCC_program.o 

C_DEPS += \
./Src/MCAL/GPIO_program.d \
./Src/MCAL/RCC_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/%.o Src/MCAL/%.su Src/MCAL/%.cyclo: ../Src/MCAL/%.c Src/MCAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL

clean-Src-2f-MCAL:
	-$(RM) ./Src/MCAL/GPIO_program.cyclo ./Src/MCAL/GPIO_program.d ./Src/MCAL/GPIO_program.o ./Src/MCAL/GPIO_program.su ./Src/MCAL/RCC_program.cyclo ./Src/MCAL/RCC_program.d ./Src/MCAL/RCC_program.o ./Src/MCAL/RCC_program.su

.PHONY: clean-Src-2f-MCAL


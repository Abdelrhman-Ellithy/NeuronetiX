################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/CLCD_program.c \
../Src/HAL/Keypad_Program.c 

OBJS += \
./Src/HAL/CLCD_program.o \
./Src/HAL/Keypad_Program.o 

C_DEPS += \
./Src/HAL/CLCD_program.d \
./Src/HAL/Keypad_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/%.o Src/HAL/%.su Src/HAL/%.cyclo: ../Src/HAL/%.c Src/HAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL

clean-Src-2f-HAL:
	-$(RM) ./Src/HAL/CLCD_program.cyclo ./Src/HAL/CLCD_program.d ./Src/HAL/CLCD_program.o ./Src/HAL/CLCD_program.su ./Src/HAL/Keypad_Program.cyclo ./Src/HAL/Keypad_Program.d ./Src/HAL/Keypad_Program.o ./Src/HAL/Keypad_Program.su

.PHONY: clean-Src-2f-HAL


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MK_ENCODER/mk_encoder.c 

OBJS += \
./MK_ENCODER/mk_encoder.o 

C_DEPS += \
./MK_ENCODER/mk_encoder.d 


# Each subdirectory must supply rules for building sources it contributes
MK_ENCODER/%.o: ../MK_ENCODER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



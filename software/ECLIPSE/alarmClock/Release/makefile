################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include WS2812/subdir.mk
-include MK_ENCODER/subdir.mk
-include I2C_TWI/subdir.mk
-include DISPLAY/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
OITiW_Budzik.lss \

FLASH_IMAGE += \
OITiW_Budzik.hex \

EEPROM_IMAGE += \
OITiW_Budzik.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: OITiW_Budzik.elf secondary-outputs

# Tool invocations
OITiW_Budzik.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,OITiW_Budzik.map -mmcu=atmega8 -o "OITiW_Budzik.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

OITiW_Budzik.lss: OITiW_Budzik.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S OITiW_Budzik.elf  >"OITiW_Budzik.lss"
	@echo 'Finished building: $@'
	@echo ' '

OITiW_Budzik.hex: OITiW_Budzik.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex OITiW_Budzik.elf  "OITiW_Budzik.hex"
	@echo 'Finished building: $@'
	@echo ' '

OITiW_Budzik.eep: OITiW_Budzik.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex OITiW_Budzik.elf  "OITiW_Budzik.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: OITiW_Budzik.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 OITiW_Budzik.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) OITiW_Budzik.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
SIZE=avr-size
AVRDUDE=avrdude
REMOVE=rm -f

PROJECT=fusebox-monitor

SOURCE_DIR=./Firmware/Source
OBJECT_DIR=./Firmware/Build/Obj
OUTPUT_DIR=./Firmware/Build

SOURCES:=$(wildcard $(SOURCE_DIR)/*.c)
OBJECTS:=$(SOURCES:$(SOURCE_DIR)/%.c=$(OBJECT_DIR)/%.o)

TARGET=$(OUTPUT_DIR)/$(PROJECT).out

HEX=$(OUTPUT_DIR)/$(PROJECT).hex
EEP=$(OUTPUT_DIR)/$(PROJECT).eep

MCU=atmega328p

HEXFORMAT=ihex

AVRDUDE_MCU=m328p
AVRDUDE_PROGRAMMERID=usbasp
AVRDUDE_PORT=usb


AVRDUDE_LFUSE=E2
AVRDUDE_HFUSE=D9
AVRDUDE_EFUSE=FF

F_CPU=8000000UL

OPTLEVEL=s

DEFINES=-DF_CPU=$(F_CPU)
INC=-I./Firmware/Include
LIBS=

CFLAGS=-I. $(INC) $(DEFINES) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall -Wstrict-prototypes

CPPFLAGS=-fno-exceptions

ASMFLAGS =-I. $(INC) -mmcu=$(MCU)        \
	-x assembler-with-cpp

LDFLAGS=-Wl,-Map,$(TARGET).map -mmcu=$(MCU) \
	-lm $(LIBS)

.PHONY: upload clean size

all: $(TARGET)

hex: $(HEX)

eep: $(EEP)

size: $(TARGET)
	@$(SIZE) -C -d --mcu=$(MCU) $(TARGET)

$(HEX): $(TARGET)
	@echo "Generating" $(HEX)
	@$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $(TARGET) $(HEX)
	@echo "Done."

$(EEP): $(TARGET)
	@echo "Generating" $(EEP)
	@$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O $(HEXFORMAT) $(TARGET) $(EEP)
	@echo "Done."

$(TARGET): $(OUTPUT_DIR) $(OBJECT_DIR) $(OBJECTS)
	@echo "Generating" $(TARGET)
	@$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Done."

$(OBJECTS): $(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $<" compiled successfully!"

clean:
	@$(RM) -R $(OUTPUT_DIR)
	@echo "Clean!"

$(OUTPUT_DIR):
	@mkdir $(OUTPUT_DIR)

$(OBJECT_DIR):
	@mkdir $(OBJECT_DIR)

upload: hex eep
	@avrdude -p$(AVRDUDE_MCU) -c$(AVRDUDE_PROGRAMMERID) -P$(AVRDUDE_PORT) -e -U flash:w:$(HEX):a -U eeprom:w:$(EEP):a -U lfuse:w:0x$(AVRDUDE_LFUSE):m -U hfuse:w:0x$(AVRDUDE_HFUSE):m -U efuse:w:0x$(AVRDUDE_EFUSE):m

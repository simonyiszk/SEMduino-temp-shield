# Name: Makefile
# Author: <insert your name here>
# Copyright: <insert your copyright message here>
# License: <insert your license reference here>

# DEVICE ....... The AVR device you compile for
# CLOCK ........ Target AVR clock rate in Hertz
# OBJECTS ...... The object files created from your source files. This list is
#                usually the same as the list of source files with suffix ".o".
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected.
# FUSES ........ Parameters for avrdude to flash the fuses appropriately.

UART_PORT  = /dev/ttyUSB0
PROJECT    = test
DEVICE     = atmega328p
PROGRAMMER = -carduino -P${UART_PORT} -b115200


######################################################################
######################################################################

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -mmcu=$(DEVICE)
CFILES     = $(wildcard *.c)
OBJECTS    = $(CFILES:.c=.o)

# symbolic targets:
all:	$(PROJECT).hex

%.o: %.c
	$(COMPILE) -c $< -o $@

#.c.o:
#	$(COMPILE) -c $< -o $@

#.S.o:
#	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

#.c.s:
#	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:$(PROJECT).hex:i

clean:
	rm -f *.hex *.elf *.o

# file targets:
$(PROJECT).elf: $(OBJECTS)
	$(COMPILE) -o $(PROJECT).elf $(OBJECTS)

$(PROJECT).hex: $(PROJECT).elf
	rm -f $(PROJECT).hex
	avr-objcopy -j .text -j .data -O ihex $(PROJECT).elf $(PROJECT).hex
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	$(PROJECT).elf
	avr-objdump -d $(PROJECT).elf

cpp:
	$(COMPILE) -E $(PROJECT).c
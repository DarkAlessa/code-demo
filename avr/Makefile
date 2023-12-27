# Makefile for AVR MCU
# by Dark Alessa
# Last updated : 19 Dec 2021

SRCDIR   := ./src
BUILDDIR := ./build

PRJ = main
CCF = $(PRJ).c
OBJ = $(PRJ).o
DEP = $(PRJ).d
ELF = $(PRJ).elf
HEX = $(PRJ).hex
EEP = $(PRJ).eep

# Commands
CC = avr-gcc
OBJCOPY = avr-objcopy
REMOVE = rm -f

# AVR
F_CPU = 16000000
MCU   = atmega328p

# Flags
CFLAGS = -Wall -Os -gdwarf-2 -fsigned-char -MD -MP
AVRFLAGS = -DF_CPU=$(F_CPU)UL -mmcu=$(MCU)
ALL_FLAGS = $(CFLAGS) $(AVRFLAGS)

all: .o.d .elf .hex .eep clean

.o.d: $(SRCDIR)/$(CCF)
	$(CC) $(ALL_FLAGS) -c $(SRCDIR)/$(CCF) -o $(BUILDDIR)/$(OBJ)

.elf: $(BUILDDIR)/$(OBJ)
	$(CC) $(AVRFLAGS) $(BUILDDIR)/$(OBJ) -o $(BUILDDIR)/$(ELF)

.hex: $(BUILDDIR)/$(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $(BUILDDIR)/$(ELF) $(BUILDDIR)/$(HEX)

.eep: $(BUILDDIR)/$(ELF)
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 \
	--no-change-warnings -O ihex $(BUILDDIR)/$(ELF) $(BUILDDIR)/$(EEP) || exit 0

clean:
	$(REMOVE) $(BUILDDIR)/$(OBJ)
	$(REMOVE) $(BUILDDIR)/$(DEP)
	$(REMOVE) $(BUILDDIR)/$(EEP)

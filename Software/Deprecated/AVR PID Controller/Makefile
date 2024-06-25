SRCDIR = src
BLDDIR = build

#Main application file name
MAIN_APP = DC_Motor_Control_Hub
#Main hex file path in windows format
MAIN_HEX_PATH = $(BLDDIR)/$(MAIN_APP).hex

# Compiler and other Section
CC = avr-gcc
#   JCOPY = avr-objcopy
# avr-objcopy -oihex -R .eeprom blink.elf blink.hex
OBJCOPY = avr-objcopy
AVRDUDE := avrdude

#Options for avr-gcc
CFLAGS = -g -Os -o $(BLDDIR)/

#Linking options for avr-gcc
LFLAGS = -Os -mmcu=atmega328p -o $(BLDDIR)/

#Options for HEX file generation
HFLAGS =  -O ihex# -R .eeprom
#Options for avrdude to burn the hex file
#MMCU model here according to avrdude options
DUDEFLAGS = -c
DUDEFLAGS += arduino #usbasp
DUDEFLAGS += -P		# usbasp doesn't want to work, but Arudino as ISP does!
DUDEFLAGS += COM4
DUDEFLAGS += -b
DUDEFLAGS += 19200
DUDEFLAGS += -v
DUDEFLAGS += -p
DUDEFLAGS += m328p
DUDEFLAGS += -F #  override signature check
DUDEFLAGS += -U flash:w:$(MAIN_HEX_PATH):i

# Sources files needed for building the application
SRC = $(MAIN_APP).c

# The headers files needed for building the application
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SRCDIR))
INCLUDE = -I. -I include/ 

# commands Section
Burn : Build
	$(AVRDUDE) $(DUDEFLAGS)
Build : $(MAIN_APP).elf
	$(OBJCOPY) $(HFLAGS) $(BLDDIR)/$< $(BLDDIR)/$(MAIN_APP).hex
	
$(MAIN_APP).elf: $(MAIN_APP).o
	$(CC) $(SRC) $(SOURCES) $(INCLUDE)$(LFLAGS)$@

$(MAIN_APP).o: $(SRC)
	$(CC) $^ $(SOURCES) $(INCLUDE)$(CFLAGS)$@
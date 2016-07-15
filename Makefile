PRG            = LedLamp
OBJ            = LedLamp.o
MCU_TARGET     = atmega16a
OPTIMIZE       = -O2

DEFS           =
LIBS           =

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

CC             = avr-gcc
CXX            = avr-g++
# Override is only needed by avr-lib build system.

override CFLAGS          = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS) -I include
override CXXFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS) -I include
override LDFLAGS         = -Wl,-Map,$(PRG).map

SOURCES=$(wildcard src/*.cpp $(LIBDIR)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=$(SOURCES:.cpp=.hpp)

all: $(PRG).elf lst text eeprom


%.o: %.cpp $(HEADERS) Makefile
	 $(CXX) $(CFLAGS) -c -o $@ $<;

$(PRG).elf: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(CFLAGS)  $^ $(LDLIBS) -o $@
     
clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak 
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

eeprom: ehex ebin esrec

ehex:  $(PRG)_eeprom.hex
ebin:  $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ \
	|| { echo empty $@ not generated; exit 0; }

%_eeprom.srec: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@ \
	|| { echo empty $@ not generated; exit 0; }

%_eeprom.bin: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@ \
	|| { echo empty $@ not generated; exit 0; }
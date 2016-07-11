::Since Makefiles hate colons outside of their usual place we write this short script used to program the avr
avrdude -pm16 -cusbasp -Uflash:w:demo.elf
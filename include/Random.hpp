#include<avr/io.h>
//This namespace contains simple LFSR pseudorandom generator with ability to seed itself with adc noise
//The ADC pins are hardcoded inside source files
namespace Random
{
	uint8_t getByte();
	//Seeds the LFSR with given seed
	void seed(uint16_t seed);
	//Seeds the LFSR with ADC noise
	void seedWithADC();
}

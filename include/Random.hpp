#include<avr/io.h>
//This namespace contains simple LFSR pseudorandom generator with ability to seed itself with adc noise
//The ADC pins are hardcoded inside source files
namespace Random
{
	uint8_t getUint8();
	uint16_t getUint16();
	uint32_t getUint32();
	//Seeds the LFSR with given seed
	void seed(uint32_t seed);
	//Seeds the LFSR with ADC noise
	void seedWithADC();
}

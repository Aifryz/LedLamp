#include"../include/Random.hpp"
#include"../include/Debug.hpp"
namespace Random
{
	static uint16_t state;
	namespace priv
	{
		bool DEBUG_ADC = true;
	}
	uint8_t getByte()
	{
		//16 bit maximal period Galois LFSR
		uint8_t lsb = state & 1;
		state >>=1;
		if(lsb)
		{
			state^=0xB400;
		}
		return state & 0x00FF;
	}
	//Seeds the LFSR with given seed
	void seed(uint16_t seed)
	{
		state = seed;
	}
	//Seeds the LFSR with ADC noise
	void seedWithADC()
	{
		state = 0;
		//Setup ADC
		/*Internal ref
		 *ADC7 input
		 */		
		ADMUX = (1<<REFS1)|(1<<REFS0)|(1<<MUX0)|(1<<MUX1)|(1<<MUX2);
		//Fastest clock->most noise(i hope)
		ADCSRA = (1<<ADEN);
		for(uint8_t i=0;i<16;i++)
		{
			ADCSRA |= (1<<ADSC);
			//Wait for complete conversion
			asm volatile(
					"AdcADSCWait_%=:	   	  \n\t"
					"sbis %[reg], %[bit]      \n\t"
					"rjmp AdcADSCWait_%=      \n\t"
					://Output
					://Input
					[reg] "I" (_SFR_IO_ADDR(ADCSRA)),
					[bit] "I" (ADSC)
					);
			volatile uint8_t low = ADCL;
			//Read high register 
			volatile uint8_t high = ADCH;
			state |= (low & 0x01)<<i;
			Debug::print("\nLow is:",priv::DEBUG_ADC);
			Debug::print_hex(low,priv::DEBUG_ADC);
		}
		Debug::print("\n Seed is: ", priv::DEBUG_ADC);
		Debug::print_hex(state&0x00FF, priv::DEBUG_ADC);
		Debug::print_hex((state&0xFF00)>>8, priv::DEBUG_ADC);
	}

}

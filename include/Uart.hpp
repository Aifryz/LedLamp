#define F_CPU 1000000UL
#include<stdint.h>
#include<avr/io.h>
#define BAUD 4800
#include<util/setbaud.h>
#ifndef UART_HPP_INCLUDED
#define UART_HPP_INCLUDED

namespace Uart
{
	inline void configure()
	{
	//uart init
	//ubbrr = 64
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	#if USE_2X
        UCSRA |= (1 << U2X);
    #else
        UCSRA &= ~(1 << U2X);
    #endif
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);//enable rx and tx and rx interrupt
	UCSRC = (1<<URSEL)|(1<<USBS)|(1<<UCSZ0)|(1<<UCSZ1);//frame format 8data+2stop


	}
	//Blocking send, does not use interrupts
    inline void send(uint8_t data)
	{
		//Wait for UDRE = 1(tx register empty)
		asm volatile(
				"UartUDREWait_%=:	   	  \n\t"
				"sbis %[reg], %[bit]  \n\t"
				"rjmp UartUDREWait_%=      "
				://Output
				://Input
				[reg] "I" (_SFR_IO_ADDR(UCSRA)),
				[bit] "I" (UDRE)
				);

		UDR = data;

	}
	inline void send(const char* string)
	{
		while(char c = *string)
		{
			send(c);
			string++;
		}
	}
}
#endif

 #define F_CPU 1000000UL
#include <avr/io.h>
#include<avr/interrupt.h>
#define BAUD 4800
#include<util/setbaud.h>
#include<util/delay.h>
#include<Uart.hpp>
void uartSend(const char* str)
{
	while(*str)
	{
	Uart::send(*str++);
	}

}

ISR(USART_RXC_vect)
{
//simple echo
	uint8_t recieved = UDR;
	UDR = recieved;
    PORTC^=(1<<PINC0);
	//reti();
}
int main(void)
{
    DDRC |=(1<<PINC0);
	//uart init
	//ubbrr = 64
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	//#if USE_2X
    //    UCSRA |= (1 << U2X);
   // #else
        UCSRA &= ~(1 << U2X);
   // #endif
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);//enable rx and tx and rx interrupt
	UCSRC = (1<<URSEL)|(1<<USBS)|(1<<UCSZ0)|(1<<UCSZ1);//frame format 8data+2stop

	sei();
    /* Replace with your application code */
    while (1) 
    {
		uartSend("uarcik dziala+++\n");
		_delay_ms(100);
    }
}


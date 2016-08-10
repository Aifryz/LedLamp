#define F_CPU 1000000UL
#include <avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include"../include/Uart.hpp"
#include"../include/TWI.hpp"
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
	uint8_t buf[8];
	buf[0]=0x80;//write
	buf[1]=0x00;//mode1 register
	buf[2]=0b00100001;
	buf[3]=0b00011011;
	twi::Transaction trans;
	trans.length = 4;
	trans.data=buf;
	trans.send_stop_flag=1;
	DDRC |=(1<<PINC0);
	sei();
	Uart::configure();
	twi::startAsyncTransaction(trans);
	sei();
	while (1) 
    {
		sei();
    }
}


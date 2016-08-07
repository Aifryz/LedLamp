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
	twi::Transaction trans;
	trans.length = 8;
	trans.data=buf;
	trans.send_stop_flag=1;
	twi::startAsyncTransaction(trans);
    DDRC |=(1<<PINC0);
	sei();
	Uart::configure();
    while (1) 
    {
		Uart::send("uarcik dziala+++\n");
		_delay_ms(100);
    }
}


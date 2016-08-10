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
uint8_t buf[8];

	static volatile uint8_t counter=0;
void call()
{
	Uart::send("callback\n");
	for(uint8_t i=0;i<8;i++)
		Uart::sendAsHex(buf[i]);
	Uart::send('\n');
	counter++;
	if(counter==2)
	{
		Uart::sendAsHex(twi::priv::current_transaction.data[0]);
		Uart::sendAsHex(twi::priv::current_transaction.data[1]);
		Uart::sendAsHex(twi::priv::current_transaction.data[2]);
		Uart::sendAsHex(twi::priv::current_transaction.data[3]);
	}
	else if(counter==1)
	{
		twi::Transaction tr;
		tr.data= buf+4;
		tr.send_stop_flag=1;
		tr.length=4;
		twi::startAsyncTransaction(tr);
	}
	else
	{
		Uart::send("Bad call\n");
	}
	return;
}

int main(void)
{
	buf[0]=0x80;//write
	buf[1]=0x00;//mode1 register
	buf[2]=0b00100001;
	buf[3]=0b00011011;

	buf[4]=0x81;//read
	buf[5]=0xAA;
	buf[6]=0xAA;
	buf[7]=0xAA;

	twi::Transaction trans;
	trans.length = 4;
	trans.data=buf;
	trans.send_stop_flag=0;
	DDRC |=(1<<PINC0);
	Uart::configure();
	Uart::send("Hello\n");
	twi::stopped_callback = &call;
	twi::startAsyncTransaction(trans);
	while (1) 
    {
		sei();
    }
}


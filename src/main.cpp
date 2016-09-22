#define F_CPU 1000000UL
#include <avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include"../include/Uart.hpp"
#include"../include/TWI.hpp"
#include"../include/Random.hpp"
#include"../include/LedController.hpp"
#include"../include/StateMachine.hpp"
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
	Uart::configure();
	Uart::send("Hello\n");
	Random::seedWithADC();
	Led::initDrivers();
	StateMachine m;
	m.update();
	while (1) 
    {
		Led::update();
		_delay_ms(20);
		sei();
    }
}


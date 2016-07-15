#include"../include/Uart.hpp"
#define F_CPU 1000000UL
#include <avr/io.h>
namespace Uart
{
    void send(uint8_t data)
    {
        while ( !( UCSRA & (1<<UDRE)) )//Wait for empty buffer
        ;
        UDR = data;
    }
}
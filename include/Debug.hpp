#include"Uart.hpp"
namespace Debug
{
//Simple disableable  wrappers over Uart::Print
void print(const char* str);
void print_hex(uint8_t number);
#ifndef NDEBUG //Debug

void print(const char* str)
{
	Uart::send(str);
}
void print_hex(uint8_t number)
{
	Uart::sendAsHex(number);
}

#else //Release

void print(const char* str){}
void print_hex(uint8_t number){}

#endif

}

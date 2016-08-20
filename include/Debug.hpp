#include"Uart.hpp"
namespace Debug
{
//Simple disableable  wrappers over Uart::Print
void print(const char* str, bool enable=true);
void print_hex(uint8_t number, bool enable=true);
#ifndef NDEBUG //Debug

void print(const char* str, bool enable)
{
	if(enable)
		Uart::send(str);
}
void print_hex(uint8_t number, bool enable)
{
	if(enable)
		Uart::sendAsHex(number);
}

#else //Release

void print(const char* str, bool enable){}
void print_hex(uint8_t number, bool enable){}

#endif

}

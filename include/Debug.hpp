#include"Uart.hpp"
#pragma once
namespace Debug
{
//Simple disableable  wrappers over Uart::Print
inline void print(const char* str, bool enable=true);
inline void print_hex(uint8_t number, bool enable=true);
#ifndef NDEBUG //Debug

inline void print(const char* str, bool enable)
{
	if(enable)
		Uart::send(str);
}
inline void print_hex(uint8_t number, bool enable)
{
	if(enable)
		Uart::sendAsHex(number);
}

#else //Release

inline void print(const char* str, bool enable){}
inline void print_hex(uint8_t number, bool enable){}

#endif

}

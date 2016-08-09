#include"../include/Uart.hpp"
namespace Uart
{
	void sendAsHex(uint8_t num)
	{
		uint8_t low = num&0x0f;
		uint8_t high = (num&0xf0)>>4;
		if(low>9)
		{
			low+='A';
		}
		else
		{
			low+='0';
		}
		if(high>9)
		{
			high+='A';
		}
		else
		{
			high+='0';
		}
		send(';');
		send(high);
		send(low);
		send(';');
	}
	void sendStr(const char* string)
	{
		while(char c = *string)
		{
			send(c);
			string++;
		}
	}
}

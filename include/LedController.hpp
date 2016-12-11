#ifndef LED_CONTROLLER_HPP
#define LED_CONTROLLER_HPP
#include"../include/PCA9685.hpp"
#include"../include/TWI.hpp"
namespace Led
{
	struct State
	{
		uint8_t profile;//Which profile is currently played
		uint8_t repeat_pos;//Which repeat of this profile is played
		uint8_t brightness_pos;//Which brightness level is currently being reached
	   	uint8_t	time;//How long since the start of current profile
		//Bresenham algorithm variables
		int16_t D;
		int16_t y;
		int16_t oldy;
		uint8_t flip:1;
		//Some more state variables
		uint8_t alive:1;
	};
	const uint8_t LED_COUNT=32;
	//namespace that stores the led states, calculates the current brightness and updates registers on the drivers  
	void initDrivers();
	void update();
	void initStates();

	namespace priv
	{
		extern twi::Transaction transaction;
		extern uint8_t buf1[8];
		extern uint8_t buf2[8];
		extern uint8_t* buf;
		extern State states[32];
		void TwiCallback();
		inline void swapBuffers()
		{
			uint8_t* tmp = transaction.data;
			transaction.data = buf;
			buf = tmp;	
		}
	}
}
#endif

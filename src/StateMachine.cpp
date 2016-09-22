#include"../include/StateMachine.hpp"
#include"../include/LedController.hpp"
#include"../include/Profiles.hpp"
/*
 * 
 *
 *
 *
 * */
void StateMachine::update()
{
	/*
	 *	handle inputs(change mode)
	 *	update profiles
	 *	update repeat
	 *	call update brightness
	 *
	 */
	for(uint8_t i=0;i<6;i++)
	{
		uint16_t data = pgm_read_word_near(profile1+i);
		Debug::print_hex(data&0x00FF,true);
		Debug::print_hex(data&0xFF00,true);
	}
	
	Led::update();
}

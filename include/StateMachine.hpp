#ifndef STATE_HPP
#define STATE_HPP
#include<stdint.h>
struct StateMachine
{	
	enum States
	{
	};
	void update();
	void checkInput();
	private:
	uint16_t m_a_stop=0;
	uint16_t m_b_stop=0;
	uint16_t m_btn_stop=0;	
	uint8_t m_old_state=0xFF;

};
#endif

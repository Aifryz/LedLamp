#include"../include/StateMachine.hpp"
#include"../include/LedController.hpp"
#include"../include/Profiles.hpp"
#include"../include/Debug.hpp"
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
	checkInput();
	for(uint8_t i = 0; i<16;i++)
	{
		Led::State st = Led::priv::states[i];
		st.profile=0;
		st.time++;
		uint8_t time;
		
		uint16_t brightness = pgm_read_word(&getProfileLocation(st.profile)[st.brightness_pos]);
		time = (brightness&0xF000)>>12;
		
		if(st.time > time*16)
		{
			//if(i==13)Debug::print("tp\n");
			//load next brightness point
			st.brightness_pos++;
			st.oldy=brightness&(0x0FFF);
			brightness = pgm_read_word(&getProfileLocation(st.profile)[st.brightness_pos]);
			time = (brightness&0xF000)>>12;

			st.time = 0;
		}
		//todo proper looping
		if(st.brightness_pos >= getProfileSize(st.profile))//end of profile
		{
			brightness = pgm_read_word(&getProfileLocation(st.profile)[st.brightness_pos-1]);
			st.oldy=brightness&(0x0FFF);

			//for now, loop to first bp
			//if(i==13)Debug::print("ps\n");
			st.brightness_pos = 0;
			//load last point
						brightness = pgm_read_word(&getProfileLocation(st.profile)[st.brightness_pos]);
			time = (brightness&0xF000)>>12;
			
			st.time=0;
			//todo repeats
			//todo profiles
		}
		//Write back state
		Led::priv::states[i]=st;
	}	
	Led::update();
}
void StateMachine::checkInput()
{
	const uint8_t A = (1<<PINA3);
	const uint8_t B = (1<<PINA4);
	const uint8_t BTN= (1<<PINA2);
	const uint16_t ENC_DELAY=0x000F;
	const uint16_t BTN_DELAY=0x000F;
	uint8_t state = PINA;
	
	if(m_a_stop == 0)
	{
		if(!(state & A) && (m_old_state & A) )
		{//falling edge on A 

			if(!(state&B))
				Debug::print("right\n");
			else
				Debug::print("left\n");

		}		
	}
	else
	{
		m_a_stop--;
	}

	//if(m_b_stop == 0)
	/*{
		if(!(state & B) && (m_old_state & B))
		{//encoder b went low
			m_b_stop = ENC_DELAY;
			if(m_a_stop != 0)
			{//a went low first
				//assume right
				
				Debug::print("left\n");
			}
		}
	}
	else
	{
		m_b_stop--;
	}*/

	if(m_btn_stop == 0)
	{
		if(!(state & BTN) && (m_old_state & BTN) )
		{//btn went low
			m_btn_stop = BTN_DELAY;	
			//btn pressed
			Debug::print("btn\n");
		}
	}
	else
	{
		m_btn_stop--;
	}

	m_old_state = state;
}

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
			if(i==13)Debug::print("tp\n");
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
			brightnes = pgm_read_word(&getProfileLocation(st.profile)[st.brightness_pos-1]);
			st.oldy=brightness&(0x0FFF);

			//for now, loop to first bp
			if(i==13)Debug::print("ps\n");
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

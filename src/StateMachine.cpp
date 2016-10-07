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
	
	const bool DEBUG=true;
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
			if(i==13)
			{
				Debug::print("bp stop: ");
				Debug::print_hex(st.brightness_pos);
				Debug::print("st.time stopped");
				Debug::print_hex(st.time);
				Debug::print("\n");
				Debug::print("bright was: ");
				Debug::print_hex((brightness&0x00FF));
				Debug::print_hex((brightness&0x0F00)>>8);
				Debug::print("\n");
			}
			//load next brightness point
			st.brightness_pos++;

			brightness = pgm_read_word(&getProfileLocation(st.profile)[st.brightness_pos]);
			time = (brightness&0xF000)>>12;
			if(i==13)
			{
				Debug::print("Loaded time: ");
				Debug::print_hex(time);
				Debug::print("\n");
			}

			st.time = 0;
		}

		if(st.brightness_pos >= getProfileSize(st.profile))//end of profile
		{
			if(i==13)
			{
				Debug::print("p stop: ");
			}
			//for now, loop to first bp
			st.brightness_pos = 0;

			brightness = pgm_read_word(&getProfileLocation(st.profile)[st.brightness_pos]);
			time = (brightness&0xF000)>>12;

			//todo repeats
			//todo profiles
		}
		//Write back state
		Led::priv::states[i]=st;
	}	
	Led::update();
}

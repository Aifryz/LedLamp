#include"../include/StateMachine.hpp"
#include"../include/LedController.hpp"
#include"../include/Profiles.hpp"
#include"../include/Debug.hpp"
#include"../include/Random.hpp"
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
	for(uint8_t i = 0; i<32;i++)
	{
		Led::State st = Led::priv::states[i];
		st.profile=0;
		st.time++;
		uint8_t time;
		if(!st.alive)//not alive->chance to spawn
		{
			if(Random::getUint16() > 0xFFF0u)//small chance to spawn
			{
				st.alive=1;
				st.profile = 0;
				st.brightness_pos=0;
				st.time=0;
				Debug::print("\nspawned led\n");
				Debug::print_hex(i);
			}	
			else continue;//still not alive, get next led to update
		}	


		uint16_t brightness = pgm_read_word(&getProfileLocation(st.profile)[st.brightness_pos]);
		time = (brightness&0xF000)>>12;
		
		if(st.time > time*16)
		{
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

			st.alive=0;
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

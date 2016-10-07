#include"../include/LedController.hpp"
#include"../include/Profiles.hpp"
#include"../include/Debug.hpp"
#include<stdlib.h>
namespace Led
{
	const bool DEBUG=false;
	void initDrivers()
	{
		priv::buf[0]=0x80;//SLA+W
		priv::buf[1]=0x00;//MODE1 register
		priv::buf[2]=0b00100001;
		priv::buf[3]=0b00011011;
	
		priv::transaction.length = 4;
		priv::transaction.data = priv::buf;
		priv::transaction.send_stop_flag=1;
		//Prepare for the next writes to be written to backbuffer
		priv::buf = priv::buf2;	

		twi::stopped_callback = nullptr;
		twi::startAsyncTransaction(priv::transaction);
	}
	namespace priv
	{
		void calculateBrightness();
		uint8_t working = 0;	
	}
	void update()
	{
		priv::calculateBrightness();
		while(twi::getEngineStatus() == twi::Status::RUNNING)
		{
			//wait for any previous transactions to complete
		}
		twi::stopped_callback = &priv::TwiCallback;
		priv::TwiCallback();
		//everything runs on interrupts so user can either: wait for all updates to be done or do some other calculations
	}
	namespace priv
	{
		twi::Transaction transaction;
		uint8_t buf1[8];
		uint8_t buf2[8];
		uint8_t* buf=buf1;
		State states[32];
		uint8_t led_counter;
		//Calculates brightness of current led(states[led_counter]) and stores it inside the buf[2:5]
		void calculateBrightness()
		{
			cli();
			State current = states[led_counter];	
			uint16_t brightness = pgm_read_word(&getProfileLocation(current.profile)[current.brightness_pos]);
			uint8_t time = (brightness&0xF000)>>12;
			brightness &=(0x0FFF);

			int16_t dx=time*16;
			int16_t dy=abs(brightness-current.oldy);
			

			if(current.time==0)
			{//init
				
				if(current.oldy>static_cast<int16_t>(brightness))
				{
					current.flip=1;
				}
				else
				{
					current.flip=0;
				}
				current.y=current.oldy;
				
				current.D=dy-dx;
				if(led_counter ==13 && current.time==0)
				{
					//Debug::print("Init time: ");
					Debug::print_hex(time);
				}
			}	
						int16_t calculated=current.y;	
			if(current.flip==1)
			{
				calculated=2*current.oldy-current.y;	
			}
			uint16_t val=calculated;
			if(led_counter==13)
			{
				Debug::print("currently out:");
				Debug::print_hex((val&0xFF00)>>8);
				Debug::print_hex(val&0x00FF);
				
				Debug::print("\n");
			}
			priv::buf[2]=0x00;
			priv::buf[3]=0x00;
			priv::buf[4]=val&0x00FF;
			priv::buf[5]=(val&0x0F00)>>8;
			
			while(current.D>=0)
			{
					//Debug::print("Init time: ");
				current.y++;
				current.D-=dx;
			}

			current.D+=dy;

			states[led_counter] = current;
			sei();
		}

		void TwiCallback()
		{
			//todo make this function work with two drivers
			priv::buf[0]=0x80;
			priv::buf[1]=PCA9685::LED_START+led_counter*4;
			priv::transaction.length = 6;

			priv::transaction.data = priv::buf;
			priv::transaction.send_stop_flag=1;

			while(twi::getEngineStatus() == twi::Status::RUNNING)
			{
				//wait for any previous transactions to complete
			}
			twi::startAsyncTransaction(priv::transaction);
			priv::swapBuffers();

			led_counter++;
			if(led_counter>=16)
			{	
				led_counter=0;
				twi::stopped_callback=nullptr;
				return;
			}
			else//still in range
			{
				calculateBrightness();
			}

		}
	}
}

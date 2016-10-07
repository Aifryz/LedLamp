#include"../include/LedController.hpp"
#include"../include/Profiles.hpp"
#include"../include/Debug.hpp"
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
			State current = states[led_counter];	

			uint16_t brightness = pgm_read_word(&getProfileLocation(current.profile)[current.brightness_pos]);
			uint8_t time = (brightness&0xF000)>>12;
			Debug::print("bproc time: ", DEBUG);
			Debug::print_hex(time, DEBUG);
			Debug::print("\n", DEBUG);
			priv::buf[2]=0x00;
			priv::buf[3]=0x00;
			priv::buf[4]=brightness&(0x00FF);
			priv::buf[5]=(brightness&(0x0F00))>>8;
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
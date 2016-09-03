#include"../include/LedController.hpp"
namespace Led
{
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
	void update()
	{
		//prepare for next transaction
		priv::buf[0]=0x80;
		priv::buf[1]=0x06;
		priv::buf[2]=0x00;
		priv::buf[3]=0x00;
		priv::buf[4]=0xFF;
		priv::buf[5]=0x0F;
		priv::transaction.length = 6;
		priv::transaction.data = priv::buf;
		priv::transaction.send_stop_flag=1;

		while(twi::getEngineStatus() == twi::Status::RUNNING)
		{
			//wait for any previous transactions to complete
		}

		twi::stopped_callback = &priv::TwiCallback;
		twi::startAsyncTransaction(priv::transaction);
		priv::swapBuffers();
	}
	namespace priv
	{
		twi::Transaction transaction;
		uint8_t buf1[8];
		uint8_t buf2[8];
		uint8_t* buf=buf1;
		State states[32];
		uint8_t led_counter=0;
	void TwiCallback()
	{
		Debug::print("callback\n");
		led_counter++;
		if(led_counter>32)
		{
			led_counter=0;
			twi::stopped_callback=nullptr;
			return;
		}
		priv::buf[0]=0x80;
		priv::buf[1]=0x0A;
		priv::buf[2]=0x00;
		priv::buf[3]=0x00;
		priv::buf[4]=0xFF;
		priv::buf[5]=0x00;
		priv::transaction.length = 6;
		priv::transaction.data = priv::buf;
		priv::transaction.send_stop_flag=1;

		while(twi::getEngineStatus() == twi::Status::RUNNING)
		{
			//wait for any previous transactions to complete
		}

		twi::startAsyncTransaction(priv::transaction);
		priv::swapBuffers();

	}
	}
}

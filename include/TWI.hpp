#ifndef TWI_HPP
#define TWI_HPP
#include<stdint.h>
#include<avr/io.h>
#include"Debug.hpp"
//This file contains implementation of master transmiter/reciever engines
namespace twi
{
	//Data pointed to by the data* should contain SLA+R/W as first element
	//[SLA+R/W][DATA0][DATA1]...[DATAlength-2]
	struct Transaction
	{
		volatile Transaction& operator=(const Transaction& other) volatile
		{
			data=other.data;
			length=other.length;
			stop_on_nack=other.stop_on_nack;
			send_stop_flag=other.send_stop_flag;
			return *this;
		}
		uint8_t* data;
		uint8_t length:6;
		uint8_t stop_on_nack:1;//If nack was received after data byte, the engine instead of calling twi::error() will generate stop condition and call normal callback.
		uint8_t send_stop_flag:1;
	};
	
	enum Status: uint8_t
	{
		STOPPED,//No transaction going on, bus is released
		PAUSED, //No transaction going on, bus is held low(happends when the transaction was setup not to generate stop condition)
		RUNNING,//Engine is working, there are still bytes to send/receive
		ERROR   //Error happened when processing transaction, more info is inside the TWSR
	};
	namespace priv
	{
		volatile Transaction current_transaction;
		volatile Status current_transaction_status;
	   	volatile uint8_t next_byte;
		const bool DEBUG_TWI=false;
	}
	enum State: uint8_t
	{
		//Common
		START_TXED=0x08,
		REPEATED_START_TXED=0x10,
		ARB_LOST=0x38,
		//Master Transmitter mode
		SLA_W_TXED_ACK=0x18,
		SLA_W_TXED_NACK=0x20,
		DATA_TXED_ACK=0x28,
		DATA_TXED_NACK=0x30,
		//Master Receiver mode
		SLA_R_TXED_ACK=0x40,
		SLA_R_TXED_NACK=0x48,
		DATA_RXED_ACK=0x50,
		DATA_RXED_NACK=0x58
		
	};
	///Performs transaction, does not use TWI interrupt but uses CPU
	///Returns STOPPED when transaction has been sucessfully finished
	///Returns ERROR when error occured
	///The actual error code can be found in TWSR register
	inline Status doTransaction(Transaction t)
	{
		return ERROR;
		Debug::print("Blocking i2c not implemented\n", priv::DEBUG_TWI);
	}	
}

#ifndef TWI_USE_INTERRUPT_ENGINE
#include<avr/interrupt.h>
namespace twi
{
	//Returns status of the engine
	//STOPPED means that the transaction has completed sucessfuly and engine is ready to process another transaction
	//RUNNING means that the transaction is beeing currently performed 
	inline Status getEngineStatus()
	{
		return priv::current_transaction_status;
	}
	//Starts engine
	//If there's pending transaction then this function will wait untill the pending transaction is completed
	inline void startAsyncTransaction(Transaction transaction)
	{
		while(priv::current_transaction_status == RUNNING)
		{
			//wait
		}
		//This line will emit warning that no volatile object will be accesed, this is normal and expected	
		priv::current_transaction = transaction;
		priv::current_transaction_status=RUNNING;
		priv::next_byte=0;
		TWBR = 0xFF;//DEBUG slow down twi for now
		//Send start
		TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWIE);
		sei();
		//The twi hardware now runs and is controlled by ISR
	}	
#ifndef TWI_ENGINE_USE_CALLBACKS
	typedef void(*Callback)();
	volatile Callback error_callback;
	volatile Callback stopped_callback;
#endif
	inline void error()
	{
#ifndef TWI_ENGINE_USE_CALLBACKS
	Debug::print("TWI error\n", priv::DEBUG_TWI);
	if(error_callback != nullptr)
		error_callback();
#endif
	}
	inline void callback()
	{
#ifndef TWI_ENGINE_USE_CALLBACKS
	if(stopped_callback != nullptr)
		stopped_callback();
#endif
	}
}

#endif
#endif

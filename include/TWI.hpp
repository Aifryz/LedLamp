#ifndef TWI_HPP
#define TWI_HPP
#include<stdint.h>
#include<avr/io.h>
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
			send_stop_flag=other.send_stop_flag;
			return *this;
		}
		uint8_t* data;
		uint8_t length:7;
		uint8_t send_stop_flag:1;
	};
	
	enum Status
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
	Status doTransaction(Transaction t)
	{
		return ERROR;
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
	inline void startAsyncTransaction(Transaction transaction)
	{
		//This line will emit warning that no volatile object will be accesed, this is normal and expected
		priv::current_transaction = transaction;
		priv::current_transaction_status=RUNNING;
		priv::next_byte=0;
		sei();
		//Send start
		TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWIE);

		//The twi hardware now runs and is controlled by ISR
	}	
#ifndef TWI_ENGINE_USE_CALLBACKS
	typedef void(*Callback)();
	volatile Callback error_callback;
	volatile Callback stoped_callback;
#endif
	inline void error()
	{
#ifndef TWI_ENGINE_USE_CALLBACKS
	if(error_callback != nullptr)
		error_callback();
#endif
	}
}

ISR(TWI_vect)
{
	using twi::State;
	using namespace twi::priv;
	switch(TWSR)
	{
		case State::START_TXED:
		case State::REPEATED_START_TXED:
			TWDR = current_transaction.data[next_byte];
			next_byte++;
			//Clear TWINT and TWSTA
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);
			break;

		case State::ARB_LOST:
				twi::error();
			break;

		//-----TX-----
		case State::SLA_W_TXED_ACK:
			TWDR = current_transaction.data[next_byte];
			next_byte++;
			//Clear TWINT and TWSTA
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);
			break;

		case State::SLA_W_TXED_NACK:
			//send stop
			twi::error();//No such device->cant recover
			break;

		case State::DATA_TXED_ACK:
			if(next_byte>=current_transaction.length)//last byte was sent
			{
				if(current_transaction.send_stop_flag==1)
				{
					TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);//Send stop
					current_transaction_status=twi::STOPPED;
				}
				current_transaction_status=twi::PAUSED;
			}
			else
			{
				TWDR = current_transaction.data[next_byte];
				next_byte++;
				//Clear TWINT and TWSTA
				TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);
			}
			break;

		case State::DATA_TXED_NACK:
			twi::error();//if len=0 possibly no err
			break;

		//-----RX-----
		case State::SLA_R_TXED_ACK:
			//clear flags and prepare for firt received byte
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);
			next_byte++;
			break;
		case State::SLA_R_TXED_NACK:
			twi::error();//so such device->cant recover
			break;
		case State::DATA_RXED_ACK:
			/*
			 * this rx is bad
			 */
			if(next_byte>=current_transaction.length)
			{
				if(current_transaction.send_stop_flag==1)
				{
					TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);//Send stop
					current_transaction_status=twi::STOPPED;
				}
					current_transaction_status=twi::PAUSED;

			}
			else
			{
				current_transaction.data[next_byte] = TWDR;
				next_byte++;
			}
			break;
		case State::DATA_RXED_NACK:
			twi::error();//same as with tx
			break;
		default:
			twi::error();
			break;
			//todo rx, cleanup

	}
}
#endif
#endif

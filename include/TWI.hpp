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
		uint8_t* data;
		uint8_t length:7;
		uint8_t send_stop_flag:1;
	};
	
	enum Status
	{
		STOPPED,
		RUNNING,
		ERROR
	};
	namespace priv
	{
		Transaction current_transaction;
		Status current_transaction_status;
		uint8_t next_byte;
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
			twi::error();//No such device->cant recover
			break;

		case State::DATA_TXED_ACK:
			if(next_byte>=current_transaction.length)//last byte was sent
			{
				//if flagstop=stop
				TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);//Send stop
				current_transaction_status=twi::STOPPED;
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
			break;
		case State::SLA_R_TXED_NACK:
			twi::error();
			break;
		case State::DATA_RXED_ACK:
			break;
		case State::DATA_RXED_NACK:
			twi::error();//same as with tx
			break;
		default:
			twi::error();
			break;
			//todo rx, cleanup

	}
		//state machine that uses TWSR
}
#endif
#endif
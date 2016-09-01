#include"../include/TWI.hpp"
namespace twi
{
	namespace priv
	{
		volatile Transaction current_transaction;
		volatile Status current_transaction_status;
	   	volatile uint8_t next_byte;
	}
	volatile Callback error_callback;
	volatile Callback stopped_callback;

}
ISR(TWI_vect)
{
	using twi::State;
	using namespace twi::priv;
	Debug::print("TWSR is: ", DEBUG_TWI);
	Debug::print_hex(TWSR, DEBUG_TWI);
	Debug::print("\n", DEBUG_TWI);
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
				TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);
				twi::error();
				
			break;

		//-----TX-----
		case State::SLA_W_TXED_ACK:
			//Load byte to transmit
			TWDR = current_transaction.data[next_byte];
			next_byte++;
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);
			break;

		case State::SLA_W_TXED_NACK://No such device->cant recover
			TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);
			twi::error();
			break;

		case State::DATA_TXED_ACK:
			if(next_byte>=current_transaction.length)//last byte was sent
			{
				if(current_transaction.send_stop_flag==1)
				{
					TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);//Send stop
					current_transaction_status=twi::STOPPED;
				}
				else
					current_transaction_status=twi::PAUSED;
				twi::callback();
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
			if(current_transaction.stop_on_nack==1)
			{
				TWCR =  (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);
				twi::callback();
			}
			else
			{
				TWCR =  (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);
				twi::error();
			}
			break;

			//-----RX-----
		case State::SLA_R_TXED_ACK:
			//clear flags and prepare for firt received byte
			if(next_byte>= current_transaction.length)//RX transmission with len=1
			{
				if(current_transaction.send_stop_flag==1)
				{
					TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);//Send stop
					current_transaction_status=twi::STOPPED;
				}
				else
				{
					current_transaction_status=twi::PAUSED;
				}
				twi::callback();
			}
			else
			{
				if(next_byte+1>=current_transaction.length)//RX transmission with len=2(addr+1read)
				{
					TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);//RX without ack
				}
				else
				{
					TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);//RX with ack
				}
			}
			break;

		case State::SLA_R_TXED_NACK:
			TWCR =  (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);
			twi::error();//no such device->cant recover
			break;

		case State::DATA_RXED_ACK:
			current_transaction.data[next_byte]=TWDR;
			next_byte++;
			if(next_byte+1>=current_transaction.length)//one byte left
			{
				TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);//RX without ack
			}
			else
			{
				TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);//RX with ack
			}
			break;

		case State::DATA_RXED_NACK:
			current_transaction.data[next_byte]=TWDR;
			if(current_transaction.send_stop_flag==1)
			{
				TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);//Send stop
				current_transaction_status=twi::STOPPED;
			}
			else
			{
				current_transaction_status=twi::PAUSED;
			}
			twi::callback();
			break;
		default:
			TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE);
			twi::error();
			break;
			//todo rx, cleanup

	}
}

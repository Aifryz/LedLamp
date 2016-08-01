#include<avr/io.h>
namespace ahcl
{
namespace uart
{
	//todo synchronous operation config
	enum config
	{
		rx_enable,
		tx_enable,
		tx_disable,
		rx_disable,
		bits_5,
		bits_6,
		bits_7,
		bits_8,
		bits_9,
		stop_1,
		stop_2,
		parity_odd,
		parity_even,
		no_parity,
		double_speed,
		single_speed,
		rx_interrput_enable,
		tx_interrupt_enable,
		rx_interrupt_disable,
		tx_interrupt_disable,
		tx_register_empty_interrupt_enable,
		tx_register_empty_interrupt_disable,

	};

	namespace priv
	{
		template<uint8_t val>
		struct force_const_8
		{
			static const uint8_t value = val;
		};

		template<config cfg>
		constexpr uint8_t set()
		{
			return 0;
		}
		template<config cfg>
		constexpr uint8_t clear()
		{
			return 0;
		}
		template<config cfg1, config cfg2, config...cfgs>
		constexpr uint8_t set()
		{
			return set<cfg1>()|set<cfg2,cfgs...>();
		}
		template<config cfg1, config cfg2, config...cfgs>
		constexpr uint8_t clear()
		{
			return clear<cfg1>()|clear<cfg2,cfgs...>();
		}
		//this register does not care about given config->ignore
		//todo tag dispatched clear/set bit selection
		template<config...cfgs>
		constexpr uint8_t ucsrc_helper()
		{
			return force_const_8<clear<cfgs...>()>::value;
		}
		template<config...cfgs>
		constexpr uint8_t ucsra_helper()
		{	
			return 0;
		}
		template<config...cfgs>
     	constexpr uint8_t ucsrb_helper()
		{
			return 0;
		}
	}
		//how to set baudrate
	// void setBaudrate<>();??
	// config option?
	template<config...cfgs>
	inline void configure()
	{
		UCSRC = priv::ucsrc_helper<cfgs...>();
		UCSRA = priv::ucsra_helper<cfgs...>();
     	UCSRB = priv::ucsrb_helper<cfgs...>();
		//todo
	}
}
}

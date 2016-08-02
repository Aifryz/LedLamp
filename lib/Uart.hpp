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
		struct ucsra_tag{};
		struct ucsrb_tag{};
		struct ucsrc_tag{};

		template<uint8_t val>
		struct force_const_8
		{
			static const uint8_t value = val;
		};

		template<class reg_tag, config cfg>
		constexpr uint8_t set()
		{
			return 0;
		}
		template<class reg_tag, config cfg>
		constexpr uint8_t clear()
		{
			return 0;
		}
		template<class reg_tag, config cfg1, config cfg2, config...cfgs>
		constexpr uint8_t set()
		{
			return set<reg_tag, cfg1>()|set<reg_tag, cfg2,cfgs...>();
		}
		template<class reg_tag, config cfg1, config cfg2, config...cfgs>
		constexpr uint8_t clear()
		{
			return clear<reg_tag, cfg1>()|clear<reg_tag, cfg2,cfgs...>();
		}
		//Here go set/clear template specializations:
		//Parity
		template<>
		constexpr uint8_t set<ucsrc_tag,parity_odd>(){return (1<<UPM1)|(1<<UPM0);  }

		template<>
		constexpr uint8_t set<ucsrc_tag,parity_even>(){return (1<<UPM1); }

		template<>
		constexpr uint8_t set<ucsrc_tag,no_parity>(){return 0; }
		//Parity cleari
		//default clear is bit not set?
		//cannot be true bit complement-> negates all bits in reg
		template<>
		constexpr uint8_t clear<ucsrc_tag,parity_odd>(){return 0;  }

		template<>
		constexpr uint8_t clear<ucsrc_tag,parity_even>(){return (1<<UPM0); }

		template<>
		constexpr uint8_t clear<ucsrc_tag,no_parity>(){return (1<<UPM0)|(1<<UPM1); }

		//Stop Bits
		template<>
		constexpr uint8_t set<ucsrc_tag, stop_1>(){return 0; }
		
		template<>
		constexpr uint8_t set<ucsrc_tag, stop_2>(){return (1<<USBS); };



		//this register does not care about given config->ignore
		//todo tag dispatched clear/set bit selection
		template<config...cfgs>
		constexpr uint8_t ucsrc_helper()
		{
			return force_const_8<clear<ucsrc_tag,cfgs...>()>::value;
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

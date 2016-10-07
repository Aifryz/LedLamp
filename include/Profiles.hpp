
#include<avr/pgmspace.h>
namespace priv
{
	inline constexpr uint16_t helper (uint16_t brightness, uint8_t time)
	{
		return (brightness&0x0FFF)|((time&0x0F)<<12); 
	}
	

	const uint16_t profile1[6] PROGMEM=
	{
		helper(0x00FF,4),helper(0x0FFF, 8),helper(0x0000,15),helper(0x000F,1),helper(0x0FF0,2),helper(0x0AAA, 1)
	};
	struct prof
	{
		template<uint8_t len>
		constexpr prof(const uint16_t(& lis)[len]):
			list(lis),
			size(len)
		{}
		const uint16_t* list;
		uint8_t size;
	};

	const constexpr prof lista[] ={
		prof(profile1)
	};
}

inline constexpr const uint16_t* getProfileLocation(uint8_t num)
{
	return priv::lista[num].list;
}
inline constexpr uint8_t getProfileSize(uint8_t num)
{
	return priv::lista[num].size;
}
inline constexpr uint8_t getProfilesAmount()
{
	return sizeof(priv::lista);
}

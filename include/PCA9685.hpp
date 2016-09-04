#ifndef PCA9685_HPP
#define PCA9685_HPP
#include<stdint.h>
namespace PCA9685
{
	enum Registers: uint8_t
	{
		MODE1         = 0x00, //Mode register 1 
		MODE2         = 0x01, //Mode register 2
		SUBADR1       = 0x02, //I2C-bus subaddress 1
		SUBADR2       = 0x03, //I2C-bus subaddress 2
		SUBADR3       = 0x04, //I2C-bus subaddress 3
		ALLCALLADR    = 0x05, //LED All Call I2C-bus address
		LED0_ON_L     = 0x06, //LED0 output and brightness control byte 0
		LED0_ON_H     = 0x07, //LED0 output and brightness control byte 1
		LED0_OFF_L    = 0x08, //LED0 output and brightness control byte 2
		LED0_OFF_H    = 0x09, //LED0 output and brightness control byte 3
		LED1_ON_L     = 0x0A, //LED1 output and brightness control byte 0
		LED1_ON_H     = 0x0B, //LED1 output and brightness control byte 1
		LED1_OFF_L    = 0x0C, //LED1 output and brightness control byte 2
		LED1_OFF_H    = 0x0D, //LED1 output and brightness control byte 3
		LED2_ON_L     = 0x0E, //LED2 output and brightness control byte 0
		LED2_ON_H     = 0x0F, //LED2 output and brightness control byte 1
		LED2_OFF_L    = 0x10, //LED2 output and brightness control byte 2
		LED2_OFF_H    = 0x11, //LED2 output and brightness control byte 3
		LED3_ON_L     = 0x12, //LED3 output and brightness control byte 0
		LED3_ON_H     = 0x13, //LED3 output and brightness control byte 1
		LED3_OFF_L    = 0x14, //LED3 output and brightness control byte 2
		LED3_OFF_H    = 0x15, //LED3 output and brightness control byte 3
		LED4_ON_L     = 0x16, //LED4 output and brightness control byte 0
		LED4_ON_H     = 0x17, //LED4 output and brightness control byte 1
		LED4_OFF_L    = 0x18, //LED4 output and brightness control byte 2
		LED4_OFF_H    = 0x19, //LED4 output and brightness control byte 3
		LED5_ON_L     = 0x1A, //LED5 output and brightness control byte 0
		LED5_ON_H     = 0x1B, //LED5 output and brightness control byte 1
		LED5_OFF_L    = 0x1C, //LED5 output and brightness control byte 2
		LED5_OFF_H    = 0x1D, //LED5 output and brightness control byte 3
		LED6_ON_L     = 0x1E, //LED6 output and brightness control byte 0
		LED6_ON_H     = 0x1F, //LED6 output and brightness control byte 1
		LED6_OFF_L    = 0x20, //LED6 output and brightness control byte 2
		LED6_OFF_H    = 0x21, //LED6 output and brightness control byte 3
		LED7_ON_L     = 0x22, //LED7 output and brightness control byte 0
		LED7_ON_H     = 0x23, //LED7 output and brightness control byte 1
		LED7_OFF_L    = 0x24, //LED7 output and brightness control byte 2
		LED7_OFF_H    = 0x25, //LED7 output and brightness control byte 3
		LED8_ON_L     = 0x26, //LED8 output and brightness control byte 0
		LED8_ON_H     = 0x27, //LED8 output and brightness control byte 1
		LED8_OFF_L    = 0x28, //LED8 output and brightness control byte 2
		LED8_OFF_H    = 0x29, //LED8 output and brightness control byte 3
		LED9_ON_L     = 0x2A, //LED9 output and brightness control byte 0
		LED9_ON_H     = 0x2B, //LED9 output and brightness control byte 1 
		LED9_OFF_L    = 0x2C, //LED9 output and brightness control byte 2 
		LED9_OFF_H    = 0x2D, //LED9 output and brightness control byte 3
		LED10_ON_L    = 0x2E, //LED10 output and brightness control byte 0
		LED10_ON_H    = 0x2F, //LED10 output and brightness control byte 1
		LED10_OFF_L   = 0x30, //LED10 output and brightness control byte 2
		LED10_OFF_H   = 0x31, //LED10 output and brightness control byte 3
		LED11_ON_L    = 0x32, //LED11 output and brightness control byte 0
		LED11_ON_H    = 0x33, //LED11 output and brightness control byte 1
		LED11_OFF_L   = 0x34, //LED11 output and brightness control byte 2
		LED11_OFF_H   = 0x35, //LED11 output and brightness control byte 3
		LED12_ON_L    = 0x36, //LED12 output and brightness control byte 0
		LED12_ON_H    = 0x37, //LED12 output and brightness control byte 1
		LED12_OFF_L   = 0x38, //LED12 output and brightness control byte 2
		LED12_OFF_H   = 0x39, //LED12 output and brightness control byte 3
		LED13_ON_L    = 0x3A, //LED13 output and brightness control byte 0
		LED13_ON_H    = 0x3B, //LED13 output and brightness control byte 1
		LED13_OFF_L   = 0x3C, //LED13 output and brightness control byte 2
		LED13_OFF_H   = 0x3D, //LED13 output and brightness control byte 3
		LED14_ON_L    = 0x3E, //LED14 output and brightness control byte 0
		LED14_ON_H    = 0x3F, //LED14 output and brightness control byte 1
		LED14_OFF_L   = 0x40, //LED14 output and brightness control byte 2
		LED14_OFF_H   = 0x41, //LED14 output and brightness control byte 3
		LED15_ON_L    = 0x42, //LED15 output and brightness control byte 0
		LED15_ON_H    = 0x43, //LED15 output and brightness control byte 1
		LED15_OFF_L   = 0x44, //LED15 output and brightness control byte 2
		LED15_OFF_H   = 0x45, //LED15 output and brightness control byte 3
		ALL_LED_ON_L  = 0xFA, //load all the LEDn_ON registers, byte 0 (write only, read zero)
		ALL_LED_ON_H  = 0xFB, //load all the LEDn_ON registers, byte 1 (write only, read zero)
		ALL_LED_OFF_L = 0xFC, //load all the LEDn_OFF registers, byte 0 (write only, read zero)
		ALL_LED_OFF_H = 0xFD, //load all the LEDn_OFF registers, byte 1 (write only, read zero)
		PRE_SCALE     = 0xFE, //prescaler for PWM output frequency
	// do not use TestMode      = 0xFF  //read/write defines the test mode to be entered

	};
	//First LED register
	const uint8_t LED_START = 0x06;
	// "*" means default value
	enum MODE1: uint8_t
	{
		// When 1*: Device responds to All Call Adress
		// When 0 : Device does not respond to All Call Adress
		ALLCALL=0,

		//When 1 : Device responds to subaddress 3
		//When 0*: Device does not respond to subaddress 3
		SUB3=1,

		//When 1 : Device responds to subaddress 2
		//When 0*: Device does not respond to subaddress 2
		SUB2=2,

		//When 1 : Device responds to subaddress 1
		//When 0*: Device does not respond to subaddress 1
		SUB1=3,

		//When 1*: Low power mode, oscillator off 
		//When 0 : Normal mode
		SLEEP=4,

		//When 1 : Register autoincrement enabled
		//When 0*: Register autoincrement disabled
		AI=5,

		//When 1 : Use external clock
		//When 0*: Use internal clock
		EXTCLK=6,

		//When 1 : When written: restarts device
		//When 0*: When written: no effect
		//Reading this bit shows state of restart logic(1:enabled 0:disabled)
		RESTART=7
	};
	enum MODE2: uint8_t
	{
		//When [1:0] 00*: LEDn=0 when ~OE=1
		//When [1:0] 01 : LEDn=1 when ~OE=1 and OUTDRV=1
		//				  LEDn=high-impedance when OUTDRV=0	
		//When [1:0] 1X : LEDn=high-impedance
		OUTNE0=0,
		OUTNE1=1,

		//When 1*: All LEDn are configured with a totem pole structure
		//When 0 : All LEDn are configured with an open-drain structure
		OUTDRV=2,

		//When 1 : Outputs change on ACK
		//When 0*: Outputs change on STOP command
		OCH=3,

		//When 1 : Output logic inverted. Use when no external driver is used
		//When 0*: Output logic not inverted. Use when external driver is used
		INVRT=4,
	};

}
#endif

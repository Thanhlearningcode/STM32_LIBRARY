#ifndef _GPIO_STM32_H_
#define _GPIO_STM32_H_
//Include library
#include "stm32f10x.h"
// read dataseet
//define data type
typedef struct
{
	uint32_t CRL; // 9.2.1 
	uint32_t CRH; // 9.2.2
	uint32_t IDR; //9.2.3
	uint32_t ODR; //9.2.4
	uint32_t BSRR; //9.2.5
	uint32_t BRR;//9.2.6
	uint32_t LCKR; //9.2.7
}GPIO_Typedef; //9.5

//GPIO memory map
typedef enum
{
	emAddressGPIOA = 0x40010800U, // U is unsigned int
	emAddressGPIOB = 0x40010C00U, 
	emAddressGPIOC = 0x40011000U,
	emAddressGPIOD=  0x40011400U, 
	emAddressGPIOE=  0x40011800U,
	emAddressGPIOF=  0x40011C00U,
	emADdressGPIOG=  0x40011C00U,
}eRegisterMap; // 3.3 

//Define register port
#define GPIOA ((GPIO_Typedef*)emAddressGPIOA)
#define GPIOB ((GPIO_Typedef*)emAddressGPIOB)
#define GPIOC ((GPIO_Typedef*)emAddressGPIOC)
#define GPIOD ((GPIO_Typedef*)emAddressGPIOD)
#define GPIOE ((GPIO_Typedef*)emAddressGPIOE)
#define GPIOF ((GPIO_Typedef*)emAddressGPIOF)
#define GPIOG ((GPIO_Typedef*)emAddressGPIOG)

//Define pin port function
typedef enum
{
	emGeneralOutputPushPull    = 0x3,//0b0011
	emGeneralOutputOpenDrain   = 0x7,//0x0111
	emAlternateOutputPushPull  = 0xB,//0b1011
	emAlternateOutputOpenDrain = 0xF,//0b1111
	emInputAnalog              = 0x0,//0b0000
	emInputFloating            = 0x4,//0b0100
	emInputPullDown            = 0x8,//0b1000
	emInputPullUp              = 0x9,//0b1001
}eConfigurationMode;

//Interface of GPIO
void ConfigurationGPIO(GPIO_Typedef* _port, uint8_t _pin, eConfigurationMode _config_mode); // set up GPIO
void GPIOSetRegValue(GPIO_Typedef* _port, const uint32_t _value);  // Port , 0 or 1
void GPIOSetBitValue(GPIO_Typedef* _port, const uint16_t _bit_position);




#endif //_GPIO_STM32_H_

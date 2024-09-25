#include "GPIO_STM32.h"

//Configuration corresponding pin port 
void ConfigurationGPIO(GPIO_Typedef* _port, uint8_t _pin, eConfigurationMode _config_mode)
{
	//Determine port to enable clock
	switch((uint32_t)_port)
	{
		case emAddressGPIOA:
			RCC->APB2ENR |= (1<<2);
			break;
		case emAddressGPIOB:
			RCC->APB2ENR |= (1<<3);
			break;
		case emAddressGPIOC:
			RCC->APB2ENR |= (1<<4);
		default:
			break;
	}
	//Configuration
	*((uint32_t*)(_port + ((uint8_t)(_pin/8))*4)) &= ~(0xF << ((uint8_t)(_pin%8))*4);
	switch(_config_mode)
	{
		case emInputPullDown:
			*((uint32_t*)(_port + ((uint8_t)(_pin/8))*4)) |= (_config_mode << ((uint8_t)(_pin%8))*4);
			_port->ODR &= ~(1<<_pin);
			break;
		case emInputPullUp:
			*((uint32_t*)(_port + ((uint8_t)(_pin/8))*4)) |= (emInputPullDown << ((uint8_t)(_pin%8))*4);
			_port->ODR |= (1<<_pin);
			break;
		default:
			*((uint32_t*)(_port + ((uint8_t)(_pin/8))*4)) |= (_config_mode << ((uint8_t)(_pin%8))*4);
			break;
	}
}

//Set value for register
void GPIOSetRegValue(GPIO_Typedef* _port, const uint32_t _value)
{
	_port->ODR = _value;
}

//Set bit value for register
void GPIOSetBitValue(GPIO_Typedef* _port, const uint16_t _bit_position)
{
	_port->ODR |= (1<<_bit_position);
}

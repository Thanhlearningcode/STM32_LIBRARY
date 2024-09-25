#ifndef _RCC_STM32_H_
#define _RCC_STM32_H_

//Include library
#include "stm32f10x.h"

//define data type
typedef struct
{
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
	uint32_t AHBSTR;
	uint32_t CFGR2;
}CLK_TypeDef;

//define base address
#define CLOCK_BASE_ADDRESS 0x40021000

#define CLK_CONTROL ((CLK_TypeDef*)CLOCK_BASE_ADDRESS)

void ClockConfiguration(void);
#endif //_RCC_STM32_H_
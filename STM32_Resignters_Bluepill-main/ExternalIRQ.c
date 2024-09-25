#include "ExternalIRQ.h"

void ConfigExternalInterrupt(void)
{
	RCC->APB2ENR |= (1<<3);
	ConfigurationGPIO(GPIOB,1,emInputPullUp);
	//AFIO
	RCC->APB2ENR |= (1<<0); //enable clock of AFIO
	AFIO->EXTICR[0] &= ~(0xf <<4);
	AFIO->EXTICR[0] |= (1<<4); //GPIOB1
	//EXT
	EXTI->RTSR &= ~(1<<1);
	EXTI->FTSR |= (1<<1);
	EXTI->IMR |= (1<<1);
	EXTI->PR |= (1<<1);
}
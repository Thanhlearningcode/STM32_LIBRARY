#include "Timer.h"


void ConfigPWM(const uint8_t percent)
{
	//Config basic timer
   //Enable clock for timer 2
	RCC->APB1ENR |= (1<<0);
	//Config timer with period equal 1 ms
	TIM2->CNT = 0;
	TIM2->PSC = 35;
	TIM2->ARR = 1000;
	TIM2->CR1 |=  (1<<7);//enable Auto reload bufffered
	TIM2->CR1 &= ~(0x3<<5);
	TIM2->CR1 &=~ (1<<4);//use up-counting
	TIM2->CR1 &=~ (1<<2);
	TIM2->CR1 &=~ (1<<1);
	//config PWM - PA0 timer2 channel 2
	RCC->APB2ENR |= (1<<2); //enable clock for port A
	GPIOA->CRL &=~ (0xF<<4);
	GPIOA->CRL |= (0xB << 4); //config pin A1 is alternate output push pull
	TIM2->CCMR1 &=~ (0x3 <<8); //output comapre mode
	TIM2->CCMR1 &=~ (0x3 <<10);
	TIM2->CCMR1 &=~ (0x7<<12);
	TIM2->CCMR1 |= (0x6<<12); //PWM 1
	TIM2->CCMR1 &=~ (1<<15);
	TIM2->CCER &= ~(1<<5);
	//Set duty
	TIM2->CCR2 = (uint16_t)((percent * 1000)/100);
	
	TIM2->EGR |=  (1<<0);
	TIM2->CCER |= (1<<4);
	TIM2->CR1 |=  (1<<0);
}

void ConfigTimer(void)
{
	//Enable clock for timer 2
	RCC->APB1ENR |= (1<<0);
	//Config timer with period equal 1 ms
	TIM2->CNT = 0;
	TIM2->PSC = 35;
	TIM2->ARR = 1000;
	TIM2->CR1 |=  (1<<7);//enable Auto reload bufffered
	TIM2->CR1 &=~ (1<<4);//use up-counting
	TIM2->CR1 &=~ (1<<2);
	TIM2->CR1 &=~ (1<<1);
	//Enable interrupt
	TIM2->DIER |= (1<<0); // enable global interrupt
	TIM2->CR1 |=  (1<<0);
	TIM2->EGR |=  (1<<0);
}

void delay_ms(int64_t _time)
{
	TIM2->EGR |= (1<<0);//reset timer
	while(!(_time < 0))
	{
		while(0x1 == (TIM2->SR & 0x1))
		{
			_time--;
			TIM2->SR &= ~(1<<0);
		}
	}
}
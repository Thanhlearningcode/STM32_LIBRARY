#include "stm32f411xe.h"
void delay(volatile uint32_t time);
uint32_t Read_adc(void);
int main(){
	RCC->AHB1ENR |= (1U<<3)|(1U<<2) ;		
	GPIOC->MODER |= (3U<<0); // ANALOG FUN GPIOC PIN0
	RCC->APB2ENR |= (1U<<8);  // CLOCK ADC1 enable	
	ADC1->SQR3 &=~ 0x0000001F	; //clear channel select bits
	ADC1->SQR3 |= 10;						//set channel	1_10	
	ADC1->SQR1 &= ~(15U<<0);	//1 Conversation
	ADC1->CR2|=(1<<0);						//EN ADC
	GPIOD->MODER &= ~GPIO_MODER_MODER13;
	GPIOD->MODER |= GPIO_MODER_MODER13_0;
	GPIOD->MODER |= GPIO_MODER_MODER12_0;
  GPIOD->ODR |= (1 << 13);  
	while(1){
		uint32_t temp = Read_adc();
		if(temp>4080){
			GPIOD->ODR |= (1<<13);
		}else{
			GPIOD->ODR &= ~(1<<13);
		}
		delay(1000);
		GPIOD->ODR ^= (1<<12);
	}
}
void delay(volatile uint32_t time){
	while(time--){
			__asm("NOP");
		}
}
uint32_t Read_adc(void)
{
	ADC1->CR2|=ADC_CR2_SWSTART;			
	while((ADC1->SR&ADC_SR_EOC)==0){__NOP();}	// wait ADC to complete
	return ADC1->DR;							
}
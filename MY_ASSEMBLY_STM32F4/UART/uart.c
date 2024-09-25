#include "stm32f411xe.h"
#include "stdio.h"
extern void UART_Init(void);
extern char RECEIV_DATA();
int main(){
//RCC->AHB1ENR |=(1<<0);
UART_Init();
		// GPIOA2 TX , GPIOA3 RX
	// GPIOA PIN8 is output- pull up 
	GPIOA->MODER&=~(3U<<16);
	GPIOA->MODER|=(1U<<16);
	GPIOA->OTYPER&=~(1U<<8);
	
	while(1){
		
	//	GPIOA->ODR|=(1U<<8);
	char a= RECEIV_DATA();
		
		if( a=='1'){
	GPIOA->ODR&=~(1U<<8);
		}
		else {
					GPIOA->ODR|=(1U<<8);
		//GPIOA->ODR&=~(1U<<8);
		}
	}
}
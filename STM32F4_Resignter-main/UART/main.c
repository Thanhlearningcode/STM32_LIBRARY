#include "stm32f411xe.h"
#include "UART.h"
void PWW(void);
	int i=0;
	int xung =0;
int main(){
 Uart_Init(9600);
PWW();
while(1){
char giaotiep= Uart_ReData();
	if(giaotiep =='1'){
		i=500;
	TIM4->CCR1 =i;
	}
	else {
		i=0;
		TIM4->CCR1 =i;
			}
	}
}
void PWW(void){
RCC->APB1ENR |=(1<<2); // RCC TIM4
RCC->AHB1ENR|=(1<<3); // GPIOD RCC
GPIOD->MODER |=(0xA<<24) ;// AF GPIOD12,13
GPIOD->MODER |=(2U<<28); // AF  GPIOD14
GPIOD->AFR[0]|=(2U<<16)|(2U<<20)|(2U<<24) ; 
TIM1->ARR=999;
TIM1->PSC=16;
TIM1->CCMR1|=(6U<<4); //PWM MODE1
TIM1->CCER=1;
TIM1->CCMR1=xung ;
TIM1->CR1=1;
}


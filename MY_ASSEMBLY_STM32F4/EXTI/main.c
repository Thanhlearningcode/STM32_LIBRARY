#include "stm32f411xe.h"
extern void EXIT_Init1(void);

void EXTI0_IRQHandler(void){

// DO Something ....
	
	EXTI->PR |=1;

}
int main(){}
/* Author: NGUYEN VAN THANH */
/* PWM GPIOD PIN12 */
#include "stm32f411xe.h"

extern void TIM3_Init(void);
extern void PWM(unsigned short duty);

int main() {
    TIM3_Init(); 
PWM(700); 
    while (1) {
       // PWM(700); 
    }

    return 0; 
}
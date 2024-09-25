/* Author: NGUYEN VAN THANH */
/* PWM GPIOD PIN12 */
#include "stm32f411xe.h"

extern void TIM4_Init(void);
extern void PWM(unsigned short duty);

int main() {
    TIM4_Init(); 

    while (1) {
        PWM(70); 
    }

    return 0; 
}

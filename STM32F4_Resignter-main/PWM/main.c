#include "stm32f411xe.h"
/* Author: Nguyen Van Thanh */
// Function prototypes


int main() {
    PWM_Init();  // Initialize PWM

    while (1) {
        PWM_Compare(700, 900);  // Set PWM duty cycle
    }
}




#include "PWM.h"

void PWM_Init(void) {
    // Enable clock for GPIOE and TIM9
    RCC->AHB1ENR |= (1U << 4);  // Clock for GPIOE
    RCC->APB2ENR |= (1U << 16); // Clock for TIM9

    // Configure GPIOE pins for alternate function (AF)
    GPIOE->MODER &= ~(0xF << 10);  // Clear bits for PE5 and PE6
    GPIOE->MODER |= (0xA << 10);   // Set alternate function mode for PE5 and PE6
    GPIOE->AFR[0] |= (3U << 20);   // Set AF03 for PE5 (TIM9_CH1)
    GPIOE->AFR[0] |= (3U << 24);   // Set AF03 for PE6 (TIM9_CH2)

    // Configure TIM9 for PWM GPIOE5 channel 1, GPIOE6 channel 2
    TIM9->CNT = 0;           // Reset counter
    TIM9->PSC = 15;          // Set prescaler (Divide by 16)
    TIM9->ARR = 999;         // Set auto-reload register (PWM period)
    TIM9->CCR1 = 0;          // Initialize CCR1 (channel 1 duty cycle)
    TIM9->CCR2 = 0;          // Initialize CCR2 (channel 2 duty cycle)
    TIM9->CR1 |= (1 << 7);   // Enable auto-reload preload
    TIM9->CCMR1 &= ~(3U << 0);  // Clear CCMR1 for channel 1
    TIM9->CCMR1 |= (6U << 4);   // Set PWM mode 1 for channel 1
    TIM9->CCMR1 &= ~(3U << 8);  // Clear CCMR1 for channel 2
    TIM9->CCMR1 |= (6U << 12);  // Set PWM mode 1 for channel 2
    TIM9->CCER |= 1;         // Enable capture/compare for channel 1
    TIM9->CCER |= (1U << 4); // Enable capture/compare for channel 2
    TIM9->CR1 |= 1;         // Enable TIM9
}

// Function to update PWM compare values
void PWM_Compare(uint16_t xung1, uint16_t xung2) {
    // Ensure xung1 and xung2 are within valid range
    if (xung1 > 999) xung1 = 999;  // Limit to TIM9->ARR value
    if (xung2 > 999) xung2 = 999;  // Limit to TIM9->ARR value

    TIM9->CCR1 = xung1;  // Set compare value for channel 1
    TIM9->CCR2 = xung2;  // Set compare value for channel 2
}
#include "stm32f4xx.h"  
float dist;
/* 
 * Author: Nguyen Van Thanh
 * Date  : September 8, 2024
 */
 void Delay3(__IO uint32_t nCount) {
    while (nCount--) {
    }
}
float HCSR04_Read(void) {
    uint32_t time, timeout;

    // Trigger pin (PD0) set to low
    GPIOD->ODR &= ~(1U << 0);
    Delay3(2);
    // Trigger pin set to high for 10µs to start the sensor
    GPIOD->ODR |= (1U << 0);
    Delay3(10);
    // Set trigger pin back to low
    GPIOD->ODR &= ~(1U << 0);
    timeout = 1000000;
    while (!(GPIOD->IDR >> 2 & 0x1)) {
        if (timeout-- == 0x00) {
            return -1; // Timeout, return -1
        }
    }

    time = 0;
    while ((GPIOD->IDR >> 2 & 0x1)) {
        time++;
        Delay3(1); 
    }

    // Calculate distance based on the time of pulse width
    dist = (float)time * ((float)0.0171821);
    return dist;
}
uint8_t TM_HCSR04_Init(void) {
    // Enable clock for GPIOD
    RCC->AHB1ENR |= (1U << 3);
    // Configure PD0 as output (Trigger)
    GPIOD->MODER &= ~(3U << 0);  // Clear mode bits for PD0
    GPIOD->MODER |= (1U << 0);   // Set PD0 as output
    GPIOD->OTYPER &= ~(1U << 0); // Set push-pull output
    GPIOD->OSPEEDR |= (1U << 0); // Set medium speed

    // Configure PD2 as input (Echo)
    GPIOD->MODER &= ~(3U << 4);  // Set PD2 as input
    GPIOD->OTYPER &= ~(1U << 2); // Set push-pull
    GPIOD->OSPEEDR |= (1U << 4); // Set medium speed
    GPIOD->PUPDR |= (2U << 4);   // Set pull-down 

    // Set trigger pin low initially
    GPIOD->ODR &= ~(1U << 0);

    // Test if the sensor is reading a valid distance
    if (HCSR04_Read() >= 0) {
        return 1; // Initialization successful
    }
    return 0; // Initialization failed
}

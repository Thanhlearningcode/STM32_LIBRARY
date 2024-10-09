#include "stm32f411xe.h"

// Author: Nguyen Van Thanh
void ADC_init() {
    // Enable the clock for ADC1
    RCC->AHB2ENR |= (1<<8);
    
    // Configure the injected sequence register for channel 16 (temperature sensor)
    uint32_t* JSQR = (uint32_t*)0x40012338; // Injected Sequence Register
    *JSQR |= (1 << 15); // Set channel 16 for JSQ4

    // Setup Control Registers
    uint32_t* CR1 = (uint32_t*)0x40012404; // Control Register 1
    uint32_t* CR2 = (uint32_t*)0x40012408; // Control Register 2
    *CR2 |= (1 << 20); // Enable continuous conversion

    // Setup the Common Control Register
    uint32_t* CCR = (uint32_t*)0x40012304; // Common Control Register
    *CCR |= (1 << 23); // Configure common functionalities
}

// Function to read the ADC value
uint16_t Read_ADC() {
    // Start the ADC conversion
    uint32_t* CR2 = (uint32_t*)0x40012408; // Control Register 2
    *CR2 |= (1 << 22); // Start conversion

    // Wait for conversion to complete
    uint32_t* SR = (uint32_t*)0x40012400; // Status Register
    while (!(*SR & (1 << 1))); // Wait until the conversion is complete

    // Read the ADC value from the injected data register
    uint32_t* JDR4 = (uint32_t*)0x40012020; // Injected Data Register 4
    return *JDR4; // Return the ADC value
}

int main() {
    uint16_t vin, temp;
    ADC_init();

    while (1) {
        uint16_t cnt = Read_ADC(); // Read the ADC value
        vin = (cnt * 3.3) / 4095; // Convert ADC value to voltage
        temp = (vin - 0.76) / 0.025; // Convert voltage to temperature
    }
}

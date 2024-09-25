#include "ADC_Library.h"

// Define descriptive macros for ADC registers and configurations
#define ADC_ENABLE_CLOCK()     (RCC->APB2ENR |= (1U << 9)) // Enable clock for ADC1
#define ADC_PRESCALER_6        (0x2U << 14)  // Prescaler value of 6 for ADC clock

#define ADC_INTERRUPT_EOC      (1U << 5)  // Interrupt on end of conversion
#define ADC_SCAN_MODE_ENABLE   (1U << 8)  // Enable scan mode
#define ADC_CONTINUOUS_ENABLE  (1U << 1)  // Continuous conversion mode
#define ADC_RIGHT_ALIGN        (0U << 11) // Right alignment of data register
#define ADC_SOFTWARE_TRIGGER   (0x7U << 17) // Software trigger for ADC
#define ADC_EXTERNAL_TRIGGER   (1U << 20)  // Enable external trigger event
#define ADC_SAMPLING_TIME_71_5 (0x6U << 0) // Sampling time of 71.5 cycles for each channel
#define ADC_CONVERSION_LENGTH_3 (0x2U << 20) // 3 channels in regular sequence

void ADC_Config(void)
{
    // Enable clock for ADC1
    ADC_ENABLE_CLOCK();
    
    // Configure ADC clock prescaler (must be less than 14 MHz)
    RCC->CFGR &= ~(0x3U << 14); // Clear previous prescaler setting
    RCC->CFGR |= ADC_PRESCALER_6; // Set prescaler to divide clock by 6

    // ADC configuration: Control Register 1 (CR1)
    ADC1->CR1 |= ADC_INTERRUPT_EOC; // Enable interrupt on end of conversion
    ADC1->CR1 |= ADC_SCAN_MODE_ENABLE; // Enable scan mode for multiple channels
    ADC1->CR1 &= ~(1U << 11); // Disable discontinuous mode
    ADC1->CR1 &= ~(0xFU << 16); // Set ADC to independent mode (clear dual mode bits)

    // ADC configuration: Control Register 2 (CR2)
    ADC1->CR2 |= ADC_CONTINUOUS_ENABLE; // Enable continuous conversion mode
    ADC1->CR2 &= ~(1U << 8);  // Disable DMA mode
    ADC1->CR2 &= ~(1U << 11); // Use right alignment for data register
    ADC1->CR2 |= ADC_SOFTWARE_TRIGGER; // Use software to start ADC conversion
    ADC1->CR2 |= ADC_EXTERNAL_TRIGGER; // Enable external trigger for starting conversions
    
    // Set sampling time for the channels
    ADC1->SMPR2 &= ~(0x7U << 0); // Clear existing sample time
    ADC1->SMPR2 |= ADC_SAMPLING_TIME_71_5; // Set sample time to 71.5 cycles for channel 0
    ADC1->SMPR2 |= (ADC_SAMPLING_TIME_71_5 << 3); // Set sample time for channel 1
    ADC1->SMPR2 |= (ADC_SAMPLING_TIME_71_5 << 6); // Set sample time for channel 2

    // Set regular sequence of ADC conversions (SQR)
    ADC1->SQR1 &= ~(0xFU << 20); // Clear previous conversion length
    ADC1->SQR1 |= ADC_CONVERSION_LENGTH_3; // Set sequence length to 3 channels
    ADC1->SQR3 = 0U; // Clear previous settings
    ADC1->SQR3 |= (0U << 0);  // First conversion: channel 0
    ADC1->SQR3 |= (1U << 5);  // Second conversion: channel 1
    ADC1->SQR3 |= (2U << 10); // Third conversion: channel 2
    
    // Enable ADC and start conversion
    ADC1->CR2 |= (1U << 0);   // Enable ADC
    ADC1->CR2 |= (1U << 22);  // Start conversion by software trigger
}

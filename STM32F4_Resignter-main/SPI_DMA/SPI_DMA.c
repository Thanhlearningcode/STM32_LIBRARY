#include "SPI_DMA.h"

// Define pin numbers for easy reference and maintainability
#define SPI1_NSS_PIN   4
#define SPI1_SCK_PIN   5
#define SPI1_MISO_PIN  6
#define SPI1_MOSI_PIN  7

// Initialize GPIO pins for SPI1
void GPIO_SPI1_Init(void) {
    // Configure PA4 (NSS) as Output Mode
    GPIOA->MODER &= ~(1U << (SPI1_NSS_PIN * 2 + 1));  // Clear bit
    GPIOA->MODER |= (1U << (SPI1_NSS_PIN * 2));       // Set output mode

    // Configure PA5, PA6, PA7 (SCK, MISO, MOSI) as Alternate Function Mode
    GPIOA->MODER &= ~(3U << (SPI1_SCK_PIN * 2));      // Clear mode bits
    GPIOA->MODER |= (2U << (SPI1_SCK_PIN * 2));       // Set AF mode

    GPIOA->MODER &= ~(3U << (SPI1_MISO_PIN * 2));     // Clear mode bits
    GPIOA->MODER |= (2U << (SPI1_MISO_PIN * 2));      // Set AF mode

    GPIOA->MODER &= ~(3U << (SPI1_MOSI_PIN * 2));     // Clear mode bits
    GPIOA->MODER |= (2U << (SPI1_MOSI_PIN * 2));      // Set AF mode

    // Set Alternate Function 5 (AF5) for SPI1 on PA5, PA6, PA7
    GPIOA->AFR[0] &= ~(0xF << (SPI1_SCK_PIN * 4));    // Clear bits
    GPIOA->AFR[0] |= (5U << (SPI1_SCK_PIN * 4));      // Set AF5 for PA5

    GPIOA->AFR[0] &= ~(0xF << (SPI1_MISO_PIN * 4));   // Clear bits
    GPIOA->AFR[0] |= (5U << (SPI1_MISO_PIN * 4));     // Set AF5 for PA6

    GPIOA->AFR[0] &= ~(0xF << (SPI1_MOSI_PIN * 4));   // Clear bits
    GPIOA->AFR[0] |= (5U << (SPI1_MOSI_PIN * 4));     // Set AF5 for PA7
}

// Initialize DMA and SPI for data transmission
void SPI1_DMA2_Stream3_TX_Init(void) {
    // Enable clock for GPIOA and DMA2
    RCC->AHB1ENR |= (1U << 0);      // Enable clock for GPIOA
    RCC->AHB1ENR |= (1U << 22);     // Enable clock for DMA2

    // Configure SPI1 settings
    SPI1->CR1 |= (1U << 0) | (1U << 1);   // Set CPHA and CPOL
    SPI1->CR1 |= (1U << 2);               // Set as Master
    SPI1->CR1 |= (1U << 3);               // Set baud rate (fPCLK/4)
    SPI1->CR1 &= ~(1U << 7);              // Use MSB first
    SPI1->CR1 |= (1U << 8) | (1U << 9);   // Enable Software Slave Management (SSM)
    SPI1->CR1 &= ~(1U << 11);             // Set 8-bit data frame format
    SPI1->CR2 |= (1U << 0) | (1U << 1);   // Enable TX, RX DMA
    SPI1->CR1 |= (1U << 6);               // Enable SPI

    // Configure DMA settings for transmission
    DMA2_Stream3->CR = 0;                 // Disable DMA Stream 3
    while ((DMA2_Stream3->CR >> 0) & 0x1); // Wait for DMA to disable

    DMA2_Stream3->CR |= (1U << 4);        // Enable transfer complete interrupt
    DMA2_Stream3->CR |= (1U << 2);        // Enable transfer error interrupt
    DMA2_Stream3->CR |= (1U << 6);        // Set direction: Memory to Peripheral
    DMA2_Stream3->CR |= (1U << 10);       // Enable memory address increment

    // Select DMA channel 3 for SPI1
    DMA2_Stream3->CR |= (1U << 25) | (1U << 26); // Channel 3
    DMA2_Stream3->CR &= ~(1U << 27);             // Clear other bits

    DMA2_Stream3->FCR |= (1U << 2);        // Disable direct mode
    DMA2_Stream3->FCR |= (3U << 0);        // Set full FIFO mode

    // Enable interrupt in NVIC for DMA2 Stream 3
    NVIC->ISER[1] = (1U << (59 - 32));     // Enable interrupt 59 (DMA2 Stream 3)
}

// Initialize DMA for receiving data
void SPI1_DMA2_Stream2_RX_Init(void) {
    // Enable clock for DMA
    RCC->AHB1ENR |= (1U << 22);            // Enable clock for DMA2

    // Configure DMA settings for reception
    DMA2_Stream2->CR = 0;                  // Disable DMA Stream 2
    while ((DMA2_Stream2->CR >> 0) & 0x1); // Wait for DMA to disable

    DMA2_Stream2->CR |= (1U << 4);         // Enable transfer complete interrupt
    DMA2_Stream2->CR |= (1U << 2);         // Enable transfer error interrupt
    DMA2_Stream2->CR &= ~(3U << 6);        // Set direction: Peripheral to Memory
    DMA2_Stream2->CR |= (1U << 10);        // Enable memory address increment

    // Select DMA channel 3 for SPI1
    DMA2_Stream2->CR |= (1U << 25) | (1U << 26); // Channel 3
    DMA2_Stream2->CR &= ~(1U << 27);             // Clear other bits

    DMA2_Stream2->FCR |= (1U << 2);        // Disable direct mode
    DMA2_Stream2->FCR |= (3U << 0);        // Set full FIFO mode

    // Enable interrupt in NVIC for DMA2 Stream 2
    NVIC->ISER[1] = (1U << (58 - 32));     // Enable interrupt 58 (DMA2 Stream 2)
}

// Function to transfer data using SPI1 and DMA
void SPI1_Transfer(uint32_t data, uint32_t size) {
    // Clear DMA interrupt flags
    DMA2->LIFCR = (1U << 25) | (1U << 27);  // Clear transfer complete and error flags

    // Set peripheral and memory addresses
    DMA2_Stream3->PAR = (uint32_t)(&(SPI1->DR)); // Set SPI1 data register address
    DMA2_Stream3->M0AR = data;                   // Set memory address
    DMA2_Stream3->NDTR = size;                   // Set number of data items

    // Enable DMA Stream 3
    DMA2_Stream3->CR |= 1U;                      // Enable DMA stream
}

// Function to receive data using SPI1 and DMA
void SPI1_Receiver(uint32_t data, uint32_t size) {
    // Clear DMA interrupt flags
    DMA2->LIFCR = (1U << 19) | (1U << 21);  // Clear transfer complete and error flags

    // Set peripheral and memory addresses
    DMA2_Stream2->PAR = (uint32_t)(&(SPI1->DR)); // Set SPI1 data register address
    DMA2_Stream2->M0AR = data;                   // Set memory address
    DMA2_Stream2->NDTR = size;                   // Set number of data items

    // Enable DMA Stream 2
    DMA2_Stream2->CR |= 1U;                      // Enable DMA stream
}

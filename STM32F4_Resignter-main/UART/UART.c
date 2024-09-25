#include "UART.h"

// UART Initialization function
void Uart_Init(uint16_t baudrate) {
    // Enable clocks for GPIOA and USART2
    RCC->AHB1ENR |= (1U << 0);  // Enable clock for GPIOA
    RCC->APB1ENR |= (1U << 17); // Enable clock for USART2

    // Configure PA2 (TX) and PA3 (RX) in alternate function mode
    GPIOA->MODER &= ~(0xFU << 4);   // Clear configuration for PA2 and PA3
    GPIOA->MODER |= (2U << 4) | (2U << 6); // Set PA2 and PA3 to alternate function mode (AF)

    // Set alternate function for PA2 and PA3 to AF7 (USART2)
    GPIOA->AFR[0] &= ~(0xFFU << 8); // Clear alternate function bits
    GPIOA->AFR[0] |= (0x7U << 8) | (0x7U << 12); // Set AF7 for both PA2 and PA3

    // Configure USART2 baud rate based on input parameter
	  switch (baudrate){
    case 9600: 
    USART2->BRR = (104U << 4) | (3U << 0); // Set baud rate to 9600 for 16 MHz clock
			break;
		case  115200:
        USART2->BRR = (8U << 4) | (0U << 0); // Set baud rate to 115200
		default:
			// Handle unsupported baud rate
			break;
    }
    // Enable Transmitter and Receiver in USART2
    USART2->CR1 |= (1U << 3) | (1U << 2); // Enable TX and RX
    USART2->CR1 |= (1U << 13); // Enable USART2

    // Optionally, you can enable USART interrupts here
}

// Function to send a byte of data over UART
void Uart_SendData(uint8_t data) {
    // Wait until TX buffer is empty (TXE bit set)
    while (!((USART2->SR >> 7) & 0x1));

    // Write the data to the data register
    USART2->DR = data;

    // Wait until transmission is complete (TC bit set)
    while (!((USART2->SR >> 6) & 0x1));
}

// Function to receive a byte of data over UART
char Uart_ReData() {
    // Wait until the data is ready to be received (RXNE bit set)
    while (!((USART2->SR >> 5) & 0x1));

    // Return the received data from the data register
    return USART2->DR;
}

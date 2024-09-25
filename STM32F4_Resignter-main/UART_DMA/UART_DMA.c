#include "UART_DMA.h"
#include "stdint.h"

#define USART2_AF7 (7U)

char Uart_Data_Buffer[SIZE];

void Uart_DMAStream5_Init_Receiver(uint16_t baudrate){
    // Enable clock for DMA1, GPIOA, and USART2
    RCC->AHB1ENR |= (1U << 17); // DMA1 clock enable
    RCC->AHB1ENR |= (1U << 0);  // GPIOA clock enable
    RCC->APB1ENR |= (1U << 17); // USART2 clock enable

    // Configure GPIOA pins PA2 (TX) and PA3 (RX) for alternate function mode
    GPIOA->MODER &= ~(0xFU << 4); // Clear mode bits for PA2 and PA3
    GPIOA->MODER |= (2U << 4);    // PA2 Alternate function mode
    GPIOA->MODER |= (2U << 6);    // PA3 Alternate function mode
    GPIOA->AFR[0] &= ~(0xFFU << 8);
    GPIOA->AFR[0] |= (USART2_AF7 << 8) | (USART2_AF7 << 12); // Alternate Function AF07 (USART2)

    // Configure USART2 for the given baud rate
    switch (baudrate) {
        case 9600:
            USART2->BRR = (104U << 4) | (1U << 0); // Baud rate 9600
            break;
        case 115200:
            USART2->BRR = (8U << 4) | 0U; // Baud rate 115200
            break;
        default:
            // Handle unsupported baud rate
            break;
    }

    // Enable USART2 transmitter and receiver
    USART2->CR1 |= (1U << 3) | (1U << 2); // Enable Transmit and Receive
    USART2->CR3 |= (1U << 6);  // Enable DMA mode for reception
    USART2->CR3 |= (1U << 7);  // Enable DMA mode for transmission
    USART2->CR1 |= (1U << 6);  // Enable USART interrupt when TC=1
    USART2->CR1 |= (1U << 13); // Enable USART

    // Disable DMA stream for reception
    DMA1_Stream5->CR &= ~(1U << 0); // Disable DMA1 Stream 5
    while ((DMA1_Stream5->CR & (1U << 0)) != 0); // Wait until DMA is disabled

    // Clear interrupt flags for Stream5
    DMA1->HIFCR = (1U << 8) | (1U << 9); // Clear flags

    // Set Peripheral Address (USART2 Data Register)
    DMA1_Stream5->PAR = (uint32_t)(&(USART2->DR));

    // Set Memory Address (Uart Data Buffer)
    DMA1_Stream5->M0AR = (uint32_t)(&Uart_Data_Buffer);

    // Set Number of Transfers
    DMA1_Stream5->NDTR = (uint16_t)SIZE;

    // Select Channel 4
    DMA1_Stream5->CR &= ~(1U << 25);
    DMA1_Stream5->CR &= ~(1U << 26);
    DMA1_Stream5->CR |= (1U << 27);

    // Set Peripheral-to-Memory mode
    DMA1_Stream5->CR &= ~(1U << 6); 
    DMA1_Stream5->CR &= ~(1U << 7);

    // Enable Circular mode
    DMA1_Stream5->CR |= (1U << 8);

    // Enable Transfer Complete interrupt
    DMA1_Stream5->CR |= (1U << 4);

    // Enable Memory Address Increment
    DMA1_Stream5->CR |= (1U << 10);

    // Enable DMA Stream
    DMA1_Stream5->CR |= (1U << 0);

    // Enable DMA Stream5 Interrupt in NVIC
    NVIC->ISER[0] |= (1U << 16);

    // Enable USART2 global interrupt (IRQ 38)
    NVIC->ISER[1] |= (1 << 6); // (38-32)=6
}

void Uart_DMAStream5_Init_Transmit(uint32_t data, uint32_t size){
    // Disable DMA stream for transmission
    DMA1_Stream6->CR &= ~(1U << 0);
    while ((DMA1_Stream6->CR & (1U << 0)) != 0); // Wait until DMA stream is disabled

    // Clear interrupt flags for stream 6
    DMA1->HIFCR = (1U << 18) | (1U << 19) | (1U << 21);

    // Set Peripheral Address (USART2 Data Register)
    DMA1_Stream6->PAR = (uint32_t)(&(USART2->DR));

    // Set Memory Address (data buffer)
    DMA1_Stream6->M0AR = data;

    // Set Number of Transfers
    DMA1_Stream6->NDTR = size;

    // Select Channel 4
    DMA1_Stream6->CR &= ~(1U << 25);
    DMA1_Stream6->CR &= ~(1U << 26);
    DMA1_Stream6->CR |= (1U << 27);

    // Enable Memory Address Increment
    DMA1_Stream6->CR |= (1U << 10);

    // Set Transfer Direction: Memory to Peripheral
    DMA1_Stream6->CR |= (1U << 6);
    DMA1_Stream6->CR &= ~(1U << 7);

    // Enable Transfer Complete interrupt
    DMA1_Stream6->CR |= (1U << 4);

    // Enable DMA stream
    DMA1_Stream6->CR |= (1U << 0);
}

void Uart_sendData(uint8_t a1){
    // Wait until the data register is empty
    while (!(USART2->SR & (1U << 7))); 
    USART2->DR = a1;  // Send data
    while (!(USART2->SR & (1U << 6)));  // Wait for transmission to complete
}

uint8_t Uart_ReData(){
    while (!(USART2->SR & (1U << 5))); // Wait for data reception
    return (uint8_t)USART2->DR;  // Return received data
}

void DMA1_Stream6_IRQHandler(void) {
    if ((DMA1->HISR) & (1U << 21)) {
        // Clear the flag
        DMA1->HIFCR |= (1U << 21);
    }
}

void UART_SendString(const char *str) {
    while (*str) {
        Uart_sendData((uint8_t)*str++);  // Send each character
    }
}

void DMA1_Stream5_IRQHandler(void) {
    if ((DMA1->HISR) & (1U << 11)) {
        // Clear the flag
        DMA1->HIFCR |= (1U << 11);
    }
}

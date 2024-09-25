#ifndef _UART_DMA_H
#define _UART_DMA_H
#include "stm32f411xe.h"
#define SIZE 5
extern char Uart_Data_Buffer[SIZE];
void Uart_DMAStream5_Init_Receiver(uint16_t baudrate);
void Uart_DMAStream5_Init_Transmit(uint32_t data, uint32_t size);
void Uart_sendData(uint8_t a1);
void DMA1_Stream6_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
void USART2_IRQHandler(void);
#endif 
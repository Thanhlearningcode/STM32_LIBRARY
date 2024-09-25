#ifndef _UART_H_
#define _UART_H_
#include "stm32f411xe.h"
void Uart_Init(uint16_t baudrate);
void Uart_SendData(uint8_t data);
char Uart_ReData();
#endif
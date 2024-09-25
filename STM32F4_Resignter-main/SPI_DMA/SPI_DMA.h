#ifndef _SPI_DMA_H_
#define _SPI_DMA_H_
#include "stm32f411xe.h"
void GPIO_SPI1_Init(void);
void SPI1_DMA2_Stream3_Init(void);
void SPI1_DMA2_Stream3_TX_Init(void);
void SPI1_Transfer(uint32_t data,uint32_t size);
void SPI1_Receiver(uint32_t data,uint32_t size);
#endif // _SPI_DMA_H_
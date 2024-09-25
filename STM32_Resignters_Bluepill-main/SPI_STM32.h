#ifndef _SPI_STM32_H
#define _SPI_STM32_H
#include "stm32f10x.h"
void SPI_init(void);
void GPIO_SPI_RCC_SLAVE(void);
void SPI_Configure_Master(void);
void SPI_send(SPI_TypeDef *spi,uint8_t *data,uint8_t size);
void SPI_receive(SPI_TypeDef *spi,uint8_t *data,uint8_t size);
void SPI_Configure_Slave(void);
#endif
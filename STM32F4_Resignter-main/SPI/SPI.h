#ifndef _SPI_H_
#define _SPI_H_

#include "stm32f411xe.h"

void SPI_Transfer(uint8_t *data, int size);
void SPI_Receiver(uint8_t *data, int size);

#endif // _SPI_H_

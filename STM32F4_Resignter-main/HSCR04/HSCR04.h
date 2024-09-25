#ifndef _HSCR04_STM32F4_H
#define _HSCR04_STM32F4_H
#include "stm32f411xe.h"
extern float dist;
float HCSR04_Read(void);
uint8_t TM_HCSR04_Init(void);
void Delay3(__IO uint32_t nCount);
#endif // _HSCR04_STM32F4_H
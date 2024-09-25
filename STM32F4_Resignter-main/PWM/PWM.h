#ifndef _PWM_H_
#define _PWM_H_
#include "stm32f411xe.h"
void PWM_Init(void);
void PWM_Compare(uint16_t xung1, uint16_t xung2);
#endif // _PWM_H_
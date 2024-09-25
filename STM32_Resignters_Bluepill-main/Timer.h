#ifndef  _TIMER_H_
#define  _TIMER_H_

//Include library
#include "stm32f10x.h"

void ConfigPWM(const uint8_t percent);
void ConfigTimer(void);
void delay_ms(int64_t _time);

#endif //_TIMER_H_
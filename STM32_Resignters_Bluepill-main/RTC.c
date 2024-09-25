#include "RCC_STM32.h"

void ClockConfiguration(void)
{
	//1. ENABLE HSE and wait for the HSE to become Ready
	CLK_CONTROL->CR |= (1<<16);
	while(!((CLK_CONTROL->CR >> 17) & 0x1))
	{
		//wait for HSE clock ready
	}
	//2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	RCC->APB1ENR |= (1<<28);
	
	//3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	FLASH->ACR = 0;
	
	//4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	CLK_CONTROL->CFGR2 &= ~(1<<16);    // PREDIV1SRC
	CLK_CONTROL->CFGR2 &= ~(0xF);      // PREDIV1
	CLK_CONTROL->CFGR  |= (1<<16);     // PLLSRC
	CLK_CONTROL->CFGR  &= ~(0xF<<18);  // Clear PLLMUL
	CLK_CONTROL->CFGR  |= (0x7 << 18); // PLLMUL
	CLK_CONTROL->CFGR  &= ~(0xF<<4);   // AHB - 72Mhz
	CLK_CONTROL->CFGR  &= ~(0x7<<11);  // APB2 - 72Mhz
	CLK_CONTROL->CFGR  |= (0x4<<8);    // APB1 - 36Mhz
	
	//5. Enable the PLL and wait for it to become ready
	CLK_CONTROL->CR |= (1<<24);
	while(!((CLK_CONTROL->CR>>25)&0x1))
	{
		//wait PLL ready
	}
	
	//6. Select the Clock Source and wait for it to be set
	CLK_CONTROL->CFGR &= ~(0x3<<0);
	CLK_CONTROL->CFGR |= (1<<0);
}
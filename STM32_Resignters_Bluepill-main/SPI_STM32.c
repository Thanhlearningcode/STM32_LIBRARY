#include "SPI_STM32.h"
#include "time.h"
void SPI_init(void){
RCC->APB2ENR |=(1<<12); /// Config clock for SPI
RCC->APB2ENR |=(1<<2); // Config GPIOA for CLK MISO MOSI // datasheet "29 page"	 
// CLEAR 
	GPIOA->CRL &= ~(15U<<16); //pin A4 - NSS - Not used. Can be used as a GPIO
		GPIOA->CRL &= ~(15U<<20); //pin A5 - SCK - Alternate function push-pull
    GPIOA->CRL &= ~(15U<<24); //pin A6 - MISO	- Input floating / Input pull-up 
		GPIOA->CRL &= ~(15U<<28); //pin A7 - MOSI - Alternate function push-pull
	// MOSI PIN Config
GPIOA->CRL|=(0x3<<16);
GPIOA->ODR |=(1<<4);
GPIOA->CRL |=(0xB<<20);
GPIOA->CRL |=(0x8<<24);
GPIOA->CRL|=(0xB<<28);
GPIOA->ODR|=(1<<6);
	  SPI1->CR1 |= (1<<0)|(1<<1);   // CPOL=1, CPHA=1
  SPI1->CR1 |= (1<<2);  // Master Mode
  SPI1->CR1 |= (3<<3);  // BR[2:0] = 011: fPCLK/16, PCLK2 = 80MHz, SPI clk = 5MHz
  SPI1->CR1 &= ~(1<<7);  // LSBFIRST = 0, MSB first
  SPI1->CR1 |= (1<<8) | (1<<9);  // SSM=1, SSi=1 -> Software Slave Management
  SPI1->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex
  SPI1->CR1 &= ~(1<<11);  // DFF=0, 8 bit data
  SPI1->CR2 = 0;
}
void SPI_send(SPI_TypeDef *spi,uint8_t *data,uint8_t size)
{
	uint8_t dem = 0U;
	for(dem = 0U;dem <size; dem++)
	{
		while(!(spi->SR&(1U<<1)))
		{
			/*wait TXE set*/
		}
		spi->DR = *(data + dem);
	}
	while(spi->SR&(1U<<7))
	{
		/*wait busy bit clear*/
	}
	if(spi->SR&(1U<<6))
	{
		uint8_t tmp = (uint8_t)spi->DR | (uint8_t)spi->SR;
		tmp = 0U;
	}
}
void GPIO_SPI_RCC_SLAVE(void){
RCC->APB2ENR |=(1<<12); /// Config clock for SPI
RCC->APB2ENR |=(1<<2);
	GPIOA->CRL&=~(0xFFFFFFF<<7); 
		GPIOA ->CRL&=~(0x1<<5); // SCK INPUT
		GPIOA ->CRL&=~(0x1<<7); 
	GPIOA->CRL |=(0x3<<6); // MISO OUT PUSH Pull 50mhz
	GPIOA->CRL &=~(0x3<<4);
}
void SPI_Configure_Slave(void){
	SPI1->CR1 &=~(1<<14); // receive mode
	SPI1 ->CR1 &=~(1<<11);
	SPI1->CR1 |=(0x3<<3);  // baud rate // fpclk/16
	SPI1->CR1 &=~(1<<1); // CPOL low
	SPI1 ->CR1 |=(1<<2);
	SPI1->CR1 &=~(1<<7); // msb
	SPI1->CR1 |=(1<<9); // software 
	SPI1 ->CR1 |=(1<<10);
		SPI1->CR2 &=~(1<<0);
	 SPI1->CR1 |= (1 << 6);   // Enable SPI	
}
void SPI_receive(SPI_TypeDef *spi,uint8_t *data,uint8_t size)
{
	uint8_t dem = 0U;
	for(dem = 0U; dem < size; dem++)
	{
		while(spi->SR&(1U<<7))
		{
			/*wait busy bit clear*/
		}
		SPI1->DR = 0U;
		while(!(spi->SR&(1U<<0)))
		{
			/*wait RXE set*/
		}
		*(data + dem) = (uint8_t)spi->DR;
	}
}
#include "I2C_LCD.h"
#include "Timer.h"

/*===========================================I2C_CONFIG===================================================*/
void i2c_init(I2C_TypeDef *i2c)
{
	if(i2c == (I2C_TypeDef *)_I2C1_ADRESS)
	{
		RCC->APB2ENR |= (1U<<3);
		GPIOB->CRL |= (15U<<24);
		GPIOB->CRL |= (15U<<28);
		
	}
	RCC->APB1ENR |= (1U<<21);
	i2c->CR1 |= (1U<<15);
	i2c->CR1 &= ~(1U<<15);
	i2c->CR2 &= ~(63U<<0);
	i2c->CR2 |= (36U<<0);
	i2c->CCR = 180U;
	i2c->TRISE = 37U;
	i2c->CR1 |= (1U<<0);
}
void i2c_start(I2C_TypeDef *i2c)
{
	i2c->CR1 |= (1U<<8);
	while(!(i2c->SR1&(1U<<0)))
	{
		
	}
	uint16_t tmp = i2c->SR1;
	tmp = 0U;
	
}
void i2c_adress(I2C_TypeDef *i2c,uint8_t adress)
{
	i2c->DR = adress;
	while(!(i2c->SR1&(1U<<1)))
	{
		
	}
	uint16_t tmp = i2c->SR1 | i2c->SR2;
	tmp = 0U;
}
void i2c_data(I2C_TypeDef *i2c,uint8_t data)
{
	while(!(i2c->SR1&(1U<<7)))
	{
		/*data empty*/
	}
	i2c->DR = data;
	while(!(i2c->SR1&(1U<<2)))
	{
		
	}
}
void i2c_mutil_data(I2C_TypeDef *i2c,uint8_t adress,uint8_t *data,uint8_t size)
{
	uint8_t dem = 0U;
	i2c_start(i2c);
	i2c_adress(i2c,adress);
	for(dem = 0U; dem<size;dem++)
	{
			while(!(i2c->SR1&(1U<<7)))
			{
				/*data empty*/
			}
			i2c->DR = *(data + dem);
	}
	while(!(i2c->SR1&(1U<<2)))
	{
		
	}
}
void i2c_stop(I2C_TypeDef *i2c)
{
	i2c->CR1 |= (1U<<9);
}
void i2c_read(I2C_TypeDef *i2c,uint8_t adress,uint8_t *data_read,uint8_t size)
{
	uint8_t length = size;
	if(length == 1U)
	{
		i2c->DR = adress;
		while(!(i2c->SR1&(1U<<1)))
		{
			
		}
		i2c->CR1 &= ~(1U<<10);//ACK =0
		uint16_t tmp = i2c->SR1 | i2c->SR2;
		tmp = 0U;
		i2c->CR1 |= (1U<<9);//stop
		while(!(i2c->SR1&(1U<<6)))
		{
			
		}
		*(data_read + size - length) = (uint8_t)i2c->DR;
	}
	else
	{
		i2c->DR = adress;
		while(!(i2c->SR1&(1U<<1)))
		{
			
		}
		uint16_t tmp = i2c->SR1 | i2c->SR2;
		tmp = 0U;
		while(length > 2U)
		{
			while(!(i2c->SR1&(1U<<6)))
			{
				
			}
			*(data_read + size - length) = (uint8_t)i2c->DR;
			i2c->CR1 |= (1U<<10);
			length--;
		}
		while(!(i2c->SR1&(1U<<6)))
		{
			
		}
		*(data_read + size - length) = (uint8_t)i2c->DR;
		length--;
		i2c->CR1 &= ~(1U<<10);
		i2c->CR1 |= (1U<<9);
		while(!(i2c->SR1&(1U<<6)))
		{
			
		}
		*(data_read + size - length) = (uint8_t)i2c->DR;
	}
}
/*===========================================I2C_CONFIG===================================================*/

/*===================================================LCD===========================================================*/
void lcd_lenh(I2C_TypeDef *i2c,uint8_t data)
{
	uint8_t nibble_high=data&(0xF0);
	uint8_t nibble_low=(data<<4)&(0xF0);
	uint8_t buf[4];
	buf[0]=nibble_high | 0x0C;
	buf[1]=nibble_high | 0x08;
	buf[2]=nibble_low | 0x0C;
	buf[3]=nibble_low | 0x08;
	i2c_mutil_data(i2c,0x4E,(uint8_t*)buf,4U);
}
void lcd_data(I2C_TypeDef *i2c,uint8_t data)
{
	uint8_t nibble_high=data&(0xF0);
	uint8_t nibble_low=(data<<4)&(0xF0);
	uint8_t buf[4];
	buf[0]=nibble_high | 0x0D;
	buf[1]=nibble_high | 0x09;
	buf[2]=nibble_low | 0x0D;
	buf[3]=nibble_low | 0x09;
	i2c_mutil_data(i2c,0x4E,(uint8_t*)buf,4U);
}
void lcd_init(I2C_TypeDef *i2c)
{
	 lcd_lenh(i2c,0x33);
   lcd_lenh(i2c,0x32);
   delay_ms(2000);
   lcd_lenh(i2c,0x28);
   delay_ms(2000);
   lcd_lenh(i2c,0x01);
   delay_ms(2000);
   lcd_lenh(i2c,0x06);
   delay_ms(2000);
   lcd_lenh(i2c,0x0C);
   delay_ms(2000);
   lcd_lenh(i2c,0x02);
   delay_ms(2000);
   lcd_lenh(i2c,0x80);
}
void lcd_string(I2C_TypeDef *i2c,const char* s)
{
	while(*s != '\0')
	{
		lcd_data(i2c,*s);
		s++;
	}
}
void lcd_gotoxy(I2C_TypeDef *i2c,uint8_t hang,uint8_t cot)
{
	uint8_t lenh=0x00;
	if(hang==1)
	{
		lenh= 0x80 + cot;
	}
	else if(hang==2)
	{
		lenh = 0xC0 + cot;
	}
	else if(hang==3)
	{
		lenh = 0x94 + cot;
	}
	else if(hang==4)
	{
		lenh = 0xD4 + cot;
	}
	lcd_lenh(i2c,lenh);
	delay_ms(2000);
}
char* covert_string(uint16_t data,char *s)
{
	uint16_t dem=0;
  uint16_t tmp=data;
  while(tmp / 10 != 0)
  {
    dem++;
    tmp=tmp/10;
  }
  dem++;
  s[dem]='\0';
  while(data / 10 != 0)
  {
    dem--;
    s[dem] = data%10 + '0';
    data=data/10;
  }
  dem--;
  s[dem] = (char)(data + '0');
  return s;
}
/*===================================================LCD===========================================================*/
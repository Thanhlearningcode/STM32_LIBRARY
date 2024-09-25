#ifndef _I2C_LCD_H_
#define _I2C_LCD_H_

#include "stm32f10x.h"

/*===========================================I2C_CONFIG===================================================*/
typedef enum
{
	_I2C1_ADRESS = 0x40005400UL,
	_I2C2_ADRESS = 0x40005800UL,
}I2C_active;
void i2c_init(I2C_TypeDef *i2c);
void i2c_start(I2C_TypeDef *i2c);
void i2c_adress(I2C_TypeDef *i2c,uint8_t adress);
void i2c_data(I2C_TypeDef *i2c,uint8_t data);
void i2c_mutil_data(I2C_TypeDef *i2c,uint8_t adress,uint8_t *data,uint8_t size);
void i2c_stop(I2C_TypeDef *i2c);
void i2c_read(I2C_TypeDef *i2c,uint8_t adress,uint8_t *data_read,uint8_t size);
/*===========================================I2C_CONFIG===================================================*/

/*===================================================LCD_CONFIG====================================================*/
void lcd_init(I2C_TypeDef *i2c);
void lcd_data(I2C_TypeDef *i2c,uint8_t data);
void lcd_lenh(I2C_TypeDef *i2c,uint8_t lenh);
void lcd_string(I2C_TypeDef *i2c,const char* s);
void lcd_gotoxy(I2C_TypeDef *i2c,uint8_t hang,uint8_t cot);
char* covert_string(uint16_t data,char *s);
/*===================================================LCD_CONFIG====================================================*/
#endif
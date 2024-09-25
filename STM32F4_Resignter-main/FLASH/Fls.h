#ifndef _FLS_H_
#define _FLS_H_

#include "Platform_Types.h"  
#include "stm32f411xe.h"    


typedef enum {
    Sector_0,
    Sector_1,
    Sector_2,
    Sector_3,
    Sector_4,
    Sector_5,
    Sector_6,
    Sector_7,
} Sector_t;


#define FLASH_KEY1         0x45670123U
#define FLASH_KEY2         0xCDEF89ABU
#define FLASH_PG_BIT       (1U << 0)  
#define FLASH_PER_BIT      (1U << 1)  
#define FLASH_START_BIT    (1U << 16) 


void Fls_UnlockFunction(void);
void Fls_EraseFunction(uint8 Sector);     
uint8 Fls_ReadFunction(uint32 addr);    
void Fls_ProgrammingFunction(uint32 addr, uint8 data);
void Fls_ProgrammingMultiByte(uint32 addr, uint8* data, uint32 size); 
   
#endif /* _FLS_H_ */

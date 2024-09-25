#include "stm32f411xe.h"
#include "Fls.h"

int main(void)
{
   
    uint32_t flash_address = 0x08020000; // Addr Flash sector 5
    uint8_t write_data = 0xAB; 
    uint8_t read_data; 


    Fls_EraseFunction(Sector_5); // Sector 5 

 
    Fls_ProgrammingFunction(flash_address, write_data);


    read_data = Fls_ReadFunction(flash_address);

   
    if (read_data == write_data)
    {
      
        while (1) {
            // Do something
        }
    }
    else
    {
        
        while (1) {
            // Do something else
        }
    }
}

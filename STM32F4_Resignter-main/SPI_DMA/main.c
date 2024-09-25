#include "stm32f411xe.h"
#include "SPI_DMA.h"



void SPI1_DMA2_Stream3_TX_Init(void);

int main(void) {
    // Initialize SPI1
  GPIO_SPI1_Init();
    
    // Initialize DMA2 Stream 3 for SPI1 TX
    SPI1_DMA2_Stream3_TX_Init();
    

    while(1) {
     
    }
    
    return 0;
}

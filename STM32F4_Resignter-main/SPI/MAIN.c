#include "stm32f411xe.h"
#include "SPI.h"

extern void SPI1_Init(void);

int main(void) {
    // Initialize SPI1
    SPI1_Init();

    // Example: Transmit and receive data over SPI1
    uint8_t txData[2] = {0x55, 0xAA};  // Data to send
    uint8_t rxData[2];                 // Buffer to store received data

    while (1) {
        // Transmit data over SPI1
        SPI_Transfer(txData, 2);

        // Receive data over SPI1
        SPI_Receiver(rxData, 2);

       
    }

    return 0; 
}

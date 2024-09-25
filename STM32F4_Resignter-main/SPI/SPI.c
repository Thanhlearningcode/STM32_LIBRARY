#include "SPI.h"
void SPI_Transfer(uint8_t *data, int size) {
    int i = 0;
    
    // Loop through the data to be transmitted
    while (i < size) {
        // Wait until the transmit buffer is empty
        while (((SPI1->SR >> 1) & 0x1) != 1) {}
        
        // Load the data into the data register for transmission
        SPI1->DR = data[i];
        i++;
    }

    // Wait until the last data is completely transmitted
    while (((SPI1->SR >> 1) & 0x1) != 1) {}
}

void SPI_Receiver(uint8_t *data, int size) {
    int i = 0;

    // Loop through the data to be received
    while (i < size) {
        // Send a dummy byte to initiate SPI clock and receive data
        SPI1->DR = 0xFF;
        
        // Wait until the receive buffer is full (data is received)
        while (((SPI1->SR) & 0x1) != 1) {}
        
        // Read the received data from the data register
        data[i] = SPI1->DR;
        i++;
    }
}

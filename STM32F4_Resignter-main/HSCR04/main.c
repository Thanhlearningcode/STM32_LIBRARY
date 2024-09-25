#include "stm32f411xe.h"
#include "HSCR04.h"

int main(void) {	

    TM_HCSR04_Init();

    while (1) {  	
        // Read distance from the HC-SR04 sensor
        float distance = HCSR04_Read();

        if (distance < 0) {
            // Handle error: distance reading failed or timeout occurred
        } else if (distance < 20) {
            // If the distance is less than 20 cm, you can add actions, like triggering an alarm or other response
        } else {

        }
    }
}

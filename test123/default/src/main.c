/**
 * @file main.c
 * @author Shash
 * @date 2026-10-28
 * @brief Main function
 */
//C:\Program Files\Microchip\xc8\v3.10\pic\include
#include "main.h"
#include "gpio.h"

#define _XTAL_FREQ 16000000

state_t state = 0;

int main(){
    gpioInit();
    buttonDebounceInit();
    ledBlinkInit();
    
    while(1) {
        __delay_ms(1);
    }
    

    return 0;
}

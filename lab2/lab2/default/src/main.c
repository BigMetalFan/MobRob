/**
 * @file main.c
 * @author Shash
 * @date 2026-10-28
 * @brief Main function
 */

#include "main.h"
#include "lcd.h"
#include "interrupts.h"
#include "measure.h"
#include "string.h"
#include "stdio.h"

int main(){
    lcdPortInit();
    lcdInit();

    enableInterrupts();
    measureInit();
    
    startMeasure();
    
    while(1) {
        char valStr[16];
        char chStr[16];
        uint8_t channel = measureResults[0]/342+1;

        sprintf(chStr, "channel: %d",channel);
        sprintf(valStr, "val: %d",measureResults[channel]);

        lcdClear();
        lcdSendString(valStr);
        lcdSetCursor(1,0);
        lcdSendString(chStr);
        __delay_ms(100);

    }
    

    return 0;
}

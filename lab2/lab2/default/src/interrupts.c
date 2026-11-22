#include "interrupts.h"

void enableInterrupts(){
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}
void __interrupt() ISR(void)
{
    if (PIR1bits.TMR2IF &&
        PIE1bits.TMR2IE)
    {
        PIR1bits.TMR2IF = 0;
        ADCON0bits.CHS = measureChannel;
        ADCON0bits.GO = 1;
    }
        if (PIR1bits.ADIF &&
        PIE1bits.ADIE)
    {
        PIR1bits.ADIF = 0;
        measureResults[measureChannel] = ((uint16_t)ADRESH << 8) | ADRESL;
        measureChannel = measureChannel<(MEASURE_COUNT-1)? measureChannel+1:0;
    }
}
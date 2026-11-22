#include "measure.h"

uint8_t measureChannel = 0;

uint16_t measureResults[4];

static void measureTimerInit(void);

void measureInit(){

    TRISA |= (_TRISA_TRISA0_MASK |
            _TRISA_TRISA1_MASK |
            _TRISA_TRISA2_MASK |
            _TRISA_TRISA3_MASK);

    ANSELA |= (_ANSELA_ANSA0_MASK |
            _ANSELA_ANSA1_MASK |
            _ANSELA_ANSA2_MASK |
            _ANSELA_ANSA3_MASK);

    ADCON0bits.CHS = 0;

    ADCON1bits.PVCFG = 0;
    ADCON1bits.NVCFG = 0;

    ADCON2bits.ADFM = 1;

    ADCON2bits.ACQT = 0b101;

    ADCON2bits.ADCS = 0b110;

    ADCON0bits.ADON = 1;
    
    PIE1bits.ADIE = 1;
    measureTimerInit();
}

static void measureTimerInit(void)
{
    T2CONbits.TMR2ON = 0;

    T2CONbits.T2CKPS = 0b10;    // Prescaler 1:16
    T2CONbits.T2OUTPS = 0b0100; // Postscaler 1:5

    PR2 = 249;             // Период 1 мс до postscaler
    TMR2 = 0;              

    PIR1bits.TMR2IF = 0;   
    PIE1bits.TMR2IE = 1;   

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void startMeasure(){
    measureChannel = 0;
    T2CONbits.TMR2ON = 1;
}
void stopMeasure(){
    T2CONbits.TMR2ON = 0;
}
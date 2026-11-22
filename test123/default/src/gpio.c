#include "gpio.h"
#include "main.h"

void gpioInit(void){
    //Светодиод
    TRISDbits.TRISD0 = 0;
    LATDbits.LATD0 = 0;
    //Светодиод 2
    TRISDbits.TRISD1 = 0;
    LATDbits.LATD1 = 0;


    //Кнопка
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 0;

    //Прерывание по кнопке
    INTCON2bits.INTEDG0 = 0;
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0IE = 1;
    INTCONbits.GIE = 1;
}

void buttonDebounceInit(void)
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

void ledBlinkInit(void){
    T1CONbits.TMR1ON = 0;

    T1CONbits.TMR1CS = 0b00; // Fosc/4
    T1CONbits.T1CKPS = 0b11; // Prescaler 1:8

    
    TMR1H = (65536UL - 62500) >> 8;
    TMR1L = (65536UL - 62500) & 0xFF;

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    T1CONbits.TMR1ON = 1;
}

static void blink(state_t state){
        switch(state){
            case DISABLE:
                LATDbits.LATD0 = 0;
                LATDbits.LATD1 = 0;
                break;
            case BLINK_FIRST_LED:
                LATDbits.LATD0 ^= 1;
                LATDbits.LATD1 = 0;
            break;
            case BLINK_BOTH_LED:
                LATDbits.LATD0 ^= 1;
                LATDbits.LATD1 ^= 1;
            break;
            case BLINK_SECOND_LED:
                LATDbits.LATD0 = 0;
                LATDbits.LATD1 ^= 1;
            break;
            
            default:
            break;
        }
}

uint8_t timCount = 4;

void __interrupt() ISR(void)
{
    if (INTCONbits.INT0IF)
    {
        INTCONbits.INT0IF = 0;
        INTCONbits.INT0IE = 0;

        TMR2 = 0;
        PIR1bits.TMR2IF = 0;
        T2CONbits.TMR2ON = 1;
    }

    if (PIR1bits.TMR2IF &&
        PIE1bits.TMR2IE)
    {
        INTCONbits.INT0IE = 0;
        PIR1bits.TMR2IF = 0;
        T2CONbits.TMR2ON = 0;  
        if(!PORTBbits.RB0){
            state  = (state+1) %STATE_ENUM_COUNT;
        }

    }
    if (PIR1bits.TMR1IF &&
        PIE1bits.TMR1IE)
    {
        PIR1bits.TMR1IF = 0;
        if(!timCount){
            blink(state);
        }
        timCount = !timCount? 4: 0;
    }
}
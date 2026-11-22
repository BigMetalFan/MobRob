#include "lcd.h"


static void lcdClk();
static void lcdSendByte(uint8_t byte);
static void lcdSendCmd(uint8_t cmd);
static void lcdSendData(uint8_t cmd);

void lcdPortInit(){

    TRISD &= ~(_TRISD_TRISD0_MASK |
            _TRISD_TRISD1_MASK |
            _TRISD_TRISD4_MASK |
            _TRISD_TRISD5_MASK |
            _TRISD_TRISD6_MASK |
            _TRISD_TRISD7_MASK);

    LATD &= ~(_LATD_LATD0_MASK  |
            _LATD_LATD1_MASK  |
            _LATD_LATD4_MASK  |
            _LATD_LATD5_MASK |
            _LATD_LATD6_MASK |
            _LATD_LATD7_MASK);

}

void lcdInit(){
    __delay_ms(40);
    LCD_SEND(0x03);
    lcdClk();
    __delay_ms(5);

    LCD_SEND(0x03);
    lcdClk();
    __delay_us(150);

    LCD_SEND(0x03);
    lcdClk();
    __delay_us(150);

    // Переход в 4-битный режим
    LCD_SEND(0x02);
    lcdClk();
    __delay_us(150);

    // Настройка дисплея
    lcdSendCmd(0x28); // 4 бита, 2 строки, 5x8
    lcdSendCmd(0x08); // Дисплей выключен
    lcdSendCmd(0x01); // Очистка
    lcdSendCmd(0x06); // Сдвиг курсора вправо
    lcdSendCmd(0x0C); // Дисплей включён
}

void lcdSendString(char* str){
    while(*str) lcdSendData(*str++);
}

void lcdClear(){
    lcdSendCmd(0x1);
}

void lcdSetCursor(uint8_t row, uint8_t col)
{
    if (row > 1 || col > 15)
        return;

    uint8_t addr = row ? 0x40 : 0x00;

    lcdSendCmd(0x80 | (addr + col));
}
//Низкий уровень

static void lcdClk(){
    E_bit = 1;
    __delay_us(2);
    E_bit = 0;
}

static void lcdSendByte(uint8_t byte){
    LCD_SEND(byte>>4);
    lcdClk();
    LCD_SEND(byte);
    lcdClk();
}

static void lcdSendCmd(uint8_t cmd){
    RS_bit = 0;
    lcdSendByte(cmd);
    if (cmd == 0x01 || cmd == 0x02)
        __delay_ms(2);
    else
        __delay_us(50);
}

static void lcdSendData(uint8_t cmd){
    RS_bit = 1;
    lcdSendByte(cmd);
    __delay_us(50);
}




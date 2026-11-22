#pragma once
#include <xc.h>
#include "config.h"

#define RS_bit LATDbits.LATD0
#define E_bit LATDbits.LATD1

#define LCD_SEND(half) LATD = (LATD & 0x0F) | (((half) & 0x0F) << 4)

void lcdPortInit();
void lcdInit();
void lcdSendString(char* str);
void lcdSetCursor(uint8_t row, uint8_t col);
void lcdClear();
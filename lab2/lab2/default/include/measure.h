#pragma once
#include <xc.h>
#include "config.h"

#define MEASURE_COUNT 4

extern uint8_t measureChannel;
extern uint16_t measureResults[4];

void measureInit();
void startMeasure();
void stopMeasure();
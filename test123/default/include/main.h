#pragma once
#include <xc.h>
#include "config.h"


typedef enum{
    DISABLE = 0,
    BLINK_FIRST_LED = 1,
    BLINK_BOTH_LED = 2,
    BLINK_SECOND_LED = 3,

    STATE_ENUM_COUNT
}state_t;


extern state_t state;
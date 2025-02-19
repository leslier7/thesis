//
// Created by Robbie on 11/13/24.
//

#ifndef BASICMATH_INSTRUCTION_COUNT_H
#define BASICMATH_INSTRUCTION_COUNT_H
#include "pico/stdlib.h"

#if PICO_PLATFORM==rp2350
void enableClockCount();

uint32_t cycleCount();
#endif

#endif //BASICMATH_INSTRUCTION_COUNT_H

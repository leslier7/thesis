//
// Created by Robbie on 11/13/24.
//

#ifndef BASICMATH_INSTRUCTION_COUNT_H
#define BASICMATH_INSTRUCTION_COUNT_H
#include "pico/stdlib.h"


void enableClockCount();

//uint32_t cycleCountReg();

uint32_t cycleCount();

uint32_t numberInstructions();


#endif //BASICMATH_INSTRUCTION_COUNT_H

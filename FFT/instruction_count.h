//
// Created by Robbie on 11/13/24.
//

#ifndef BASICMATH_INSTRUCTION_COUNT_H
#define BASICMATH_INSTRUCTION_COUNT_H
#include "pico/stdlib.h"


void enableClockCount();

//uint32_t cycleCountReg();

uint64_t cycleCount();
uint64_t numberInstructions();

#ifdef ARCH_ARM


#elif ARCH_RISC


#endif

#endif //BASICMATH_INSTRUCTION_COUNT_H

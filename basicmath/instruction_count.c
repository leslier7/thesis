//
// Created by Robbie on 11/13/24.
//

#include "instruction_count.h"
#include "pico/stdlib.h"
#include <stdio.h>

//Code for counting the processor cycles and instructions in ARM
#if PICO_PLATFORM==rp2350
#include "hardware/structs/m33.h"

//uint32_t cycleCount = m33_hw->dwt_cyccnt; //This should get the number of clock cycles

void enableClockCount(){
    m33_hw->demcr |= (1 << 24); // Set the 24th bit of the demcr register (TRCENA) to 1 to enable DWT
    m33_hw->dwt_ctrl |= (1 << 0); //sets first bit of dwt_ctrl (CYCCNTENA) to 1 to enable dwt_cyccnt
    printf("Enabled clock count\n");
}

uint32_t cycleCount(){
    return m33_hw->dwt_cyccnt; //This should get the number of clock cycles
}

#endif

//Code for counting the processor cycles and instructions in RISC-V
#if PICO_PLATFORM==rp2350-riscv




#endif
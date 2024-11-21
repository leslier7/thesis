//
// Created by Robbie on 11/13/24.
//

#include "instruction_count.h"
#include "pico/stdlib.h"
#include <stdio.h>

//Code for counting the processor cycles and instructions in ARM
#if PICO_PLATFORM==rp2350
#include "hardware/structs/m33.h"
#include "hardware/regs/m33.h"

//uint32_t cycleCount = m33_hw->dwt_cyccnt; //This should get the number of clock cycles

void enableClockCount(){
    m33_hw->demcr |= (1 << 24); // Set the 24th bit of the demcr register (TRCENA) to 1 to enable DWT
    m33_hw->dwt_ctrl |= (1 << 0); //sets first bit of dwt_ctrl (CYCCNTENA) to 1 to enable dwt_cyccnt
    m33_hw->dwt_ctrl |= (1 << 17); //sets CPIEVTENA to 1 to enable DWT_CPICNT
    m33_hw->dwt_ctrl |= (1 << 18); //sets EXCEVTENA to 1 to enable DWT_EXCCNT
    m33_hw->dwt_ctrl |= (1 << 19); //sets SLEEPEVTENA to 1 to enable DWT_SLEEPCNT
    m33_hw->dwt_ctrl |= (1 << 20); //sets LSUEVTENA to 1 to enable DWT_LSUCNT
    m33_hw->dwt_ctrl |= (1 << 21); //sets FOLDEVTENA to 1 to enable DWT_FOLDCNT
    printf("Enabled clock count\n");
}

#define DWT_CPICNT _u(0x00001008)
#define DWT_SLEEPCNT _u(0x00001010)

#define DWT_CPICNT_VAL (*(volatile uint32_t *)(PPB_BASE + DWT_CPICNT) & 0xFF);
#define DWT_SLEEPCNT_VAL (*(volatile uint32_t *)(PPB_BASE + DWT_SLEEPCNT) & 0xFF);


uint32_t cycleCountReg(){
    return *(volatile uint32_t *)(PPB_BASE + M33_DWT_CYCCNT_OFFSET);
}

uint32_t cycleCount(){
    return m33_hw->dwt_cyccnt; //This should get the number of clock cycles
}

uint32_t numberInstructions(){ // number of instructions = CYCCNT - CPICNT - EXCCNT - SLEEPCNT - LSUCNT + FOLDCNT
    //Missing CPICNT and SLEEPCNT registers
    return m33_hw->dwt_cyccnt - DWT_CPICNT_VAL - m33_hw->dwt_exccnt -  DWT_SLEEPCNT_VAL - m33_hw->dwt_lsucnt + m33_hw->dwt_foldcnt;
    //return -1;
}

//Code for counting the processor cycles and instructions in RISC-V
#elif PICO_PLATFORM==rp2350-riscv
#include "hardware/regs/rvcsr.h"

void enableClockCount(){
    uint32_t *mcountinhibit = (uint32_t *)RVCSR_MCOUNTINHIBIT_OFFSET;
    *mcountinhibit &= ~RVCSR_MCOUNTINHIBIT_IR_BITS; // Clear the IR bit
    printf("Enabled Counter")
};

uint32_t cycleCount(){
    return -1;
};

uint32_t numberInstructions(){
    return -1;
};


#endif


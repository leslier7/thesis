//
// Created by Robbie on 11/13/24.
//

#include "instruction_count.h"
#include "pico/stdlib.h"
#include <stdio.h>

//Code for counting the processor cycles and instructions in ARM
#if ARCH_ARM
#include "hardware/structs/m33.h"
#include "hardware/regs/m33.h"

//uint32_t cycleCount = m33_hw->dwt_cyccnt; //This should get the number of clock cycles

void enableClockCount() {
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

#define DWT_CPICNT_VAL (*(volatile uint32_t *)(PPB_BASE + DWT_CPICNT) & 0xFF)
#define DWT_SLEEPCNT_VAL (*(volatile uint32_t *)(PPB_BASE + DWT_SLEEPCNT) & 0xFF)


uint32_t cycleCountReg() {
    return *(volatile uint32_t *) (PPB_BASE + M33_DWT_CYCCNT_OFFSET);
}

uint64_t cycleCount() {
    return m33_hw->dwt_cyccnt; //This should get the number of clock cycles
}

uint64_t numberInstructions() { // number of instructions = CYCCNT - CPICNT - EXCCNT - SLEEPCNT - LSUCNT + FOLDCNT
    //Missing CPICNT and SLEEPCNT registers
    return m33_hw->dwt_cyccnt - DWT_CPICNT_VAL
    -m33_hw->dwt_exccnt - DWT_SLEEPCNT_VAL
    -m33_hw->dwt_lsucnt + m33_hw->dwt_foldcnt;
    //return -1;
}

//Code for counting the processor cycles and instructions in RISC-V
#elif ARCH_RISC
#include "hardware/regs/rvcsr.h"

// These are also defined in the reg file, mostly for reference
//#define MCOUNTINHIBIT _u(0x320) //used to enable the counters
#define MCOUNTINHIBIT 0x320 // used to enable the counters

#define MCOUNTEREN 0x306 //Used to allow users to access counters. Neeed to enable

#define MINSTRET 0xb02 //Single instruction retire counter, low half
#define MINSTRETH 0xb82 //High half instruction retire counter

#define MCYCLE 0xb00
#define MCYCLEH 0xb80

#define CLEAR_BIT_0 (1U << 0)
#define CLEAR_BIT_2 (1U << 2)

#define MCOUNTINHIBIT_IR_MSB 2
#define MCOUNTINHIBIT_CY_MSB 0

//Function to read from a CSR
static inline uint32_t readCSR(const uint32_t csr) {
    uint32_t value;
    asm volatile ("csrr %0, %1" : "=r"(value) : "n"(csr)); // Use "I" for immediate
    return value;
}

//Function to write to a CSR
static inline void writeCSR(const uint32_t csr, uint32_t value) {
    asm volatile ("csrw %1, %0" :: "r"(value), "n"(csr));
}


//This crashes the program if optimization is turned off
void enableClockCount() {
    uint32_t value;
    uint32_t accessValue;
    //Enabling the user to access the registers
    accessValue = readCSR(MCOUNTEREN);

    accessValue = readCSR(MCOUNTEREN);
    printf("The value at the access register is %lb\n", accessValue);

    // Set bits 0 and 2 to 1
    accessValue |= (1U << 0) | (1U << 2);

    // Write the modified value back to the CSR
    writeCSR(MCOUNTEREN, accessValue);

    accessValue = readCSR(MCOUNTEREN);
    printf("The value at the access register is now %lb\n", accessValue);

    printf("Enabling the counter registers.\n");
    // Read MCOUNTINHIBIT register
    asm volatile ("csrr %0, %1" : "=r"(value) : "i"(MCOUNTINHIBIT));
    printf("The value at the register is %lb\n", (unsigned long)value);

    // Modify the register (set IR and CY bits)
    value &= ~((1U << MCOUNTINHIBIT_IR_MSB) | (1U << MCOUNTINHIBIT_CY_MSB));

    printf("The value of the register should now be: %lb\n", value);


    // Write modified value back to MCOUNTINHIBIT
    asm volatile ("csrw %0, %1" :: "i"(MCOUNTINHIBIT), "r"(value));

    // Read again to verify
    asm volatile ("csrr %0, %1" : "=r"(value) : "i"(MCOUNTINHIBIT));
    printf("The updated value at the register is %lb\n", (unsigned long)value);

//    uint32_t value = *(volatile uint32_t *)(RVCSR_MCOUNTINHIBIT_OFFSET);
//    //printf("The value at the register is %lu\n", value);
//    uint32_t ir_value = *(volatile uint32_t *)(RVCSR_MCOUNTINHIBIT_OFFSET);
//    uint32_t cy_value = *(volatile uint32_t *)(RVCSR_MCOUNTINHIBIT_OFFSET);
//    ir_value = (ir_value >> RVCSR_MCOUNTINHIBIT_IR_MSB) & 1U;
//    cy_value = (cy_value >> RVCSR_MCOUNTINHIBIT_CY_MSB) & 1U;
//    printf("The IR value is %lu and the CY value is %lu\n", ir_value, cy_value);
//
//    // Set the IR and CY bits
//    value |= ((1U << RVCSR_MCOUNTINHIBIT_IR_MSB) | (1U << RVCSR_MCOUNTINHIBIT_CY_MSB));
//
//    // Write the modified value back to the register
//    *(volatile uint32_t *)(RVCSR_MCOUNTINHIBIT_OFFSET) = value;
//
//   // *(volatile uint32_t *)(RVCSR_MCOUNTINHIBIT_OFFSET) |= ((1U << RVCSR_MCOUNTINHIBIT_IR_MSB) | (1U << RVCSR_MCOUNTINHIBIT_CY_MSB));
//   // value = *(volatile uint32_t *)(RVCSR_MCOUNTINHIBIT_OFFSET);
//    //printf("The value at the register is now %lu\n", value);
//    ir_value = (ir_value >> RVCSR_MCOUNTINHIBIT_IR_MSB) & 1U;
//    cy_value = (cy_value >> RVCSR_MCOUNTINHIBIT_CY_MSB) & 1U;
//    printf("The IR value is now %lu and the CY value is now %lu\n", ir_value, cy_value);
}

uint64_t cycleCount(){
    uint32_t high = readCSR(MCYCLE);
    uint32_t low = readCSR(MCYCLEH);
    printf("Low value of cycle count: %lu\n", low);
    return ((uint64_t)high << 32) | low; // Combine high and low into a 64-bit value
}

//This should return 0 I think if the register isn't enabled, but it returns like 160000 so its wrong
uint64_t numberInstructions(){
//    uint32_t high = readCSR(MINSTRET);
//    uint32_t low = readCSR(MINSTRETH);
//    printf("Low value of instruction count: %lu\n", low);
//    printf("High value of instruction count: %lu\n", high);
//    uint64_t returnValue = ((uint64_t)high << 32) | low; // Combine high and low into a 64-bit value
//    printf("Return value: %llu\n", returnValue);
//    return returnValue;
    uint32_t high1, high2, low;
    do {
        high1 = readCSR(MINSTRETH); // Read high part first
        low = readCSR(MINSTRET);    // Read low part
        high2 = readCSR(MINSTRETH); // Read high part again
    } while (high1 != high2); // Ensure no overflow occurred while reading

    printf("Low value of instruction count: %lu\n", low);
    printf("High value of instruction count: %lu\n", high1);

    uint64_t returnValue = ((uint64_t)high1 << 32) | low;
    printf("Return value: %llu\n", returnValue);
    return returnValue;

}

#endif
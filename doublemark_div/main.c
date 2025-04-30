#include <stdio.h>
#include <math.h>
#include "hardware/structs/otp.h"
#include "pico/stdlib.h"
#include "instruction_count.h"
#include "power_functions.h"
#include "hardware/regs/m33.h"

/* The printf's may be removed to isolate just the math calculations */

uint64_t tempCycles, prevTempCycles, tempLSU, prevTempLSU, tempCPI, prevTempCPI, tempEXC, prevTempEXC, tempSLEEP, prevTempSLEEP, tempFOLD, prevTempFOLD;
int instruction_overflows = 0;
int lsu_overflows = 0;
int cpi_overflows = 0;
int exc_overflows = 0;
int sleep_overflows = 0;
int fold_overflows = 0;

int main(void) {

    stdio_init_all();
    //sleep_ms(5000);
    printf("Hello Doublemark Div!\n");

    //Used to confirm which arch is running
    uint32_t archReg = otp_hw->archsel_status;
    bool arch = (archReg & 0x1); //0 is arm and 1 is risc-v
    if (arch) {
        printf("Hello from RISC-V!\n");
    } else {
        printf("Hello from ARM!\n");
    }

    initPowerTesting();
    enableClockCount();

    startBenchmark();
    sleep_ms(50);
    //Variables used for testing operations. _f means float and _d means double
    double a_d, b_d, c_d;

    //Variables used to capture times
    uint64_t instructions1, instructions2;
    uint64_t cycles1, cycles2;
    uint64_t time1, time2;

    printf("\n");
    printf("Double division.\n");
    startPowerTesting();
    time1 = time_us_64();
    cycles1 = cycleCount();
    instructions1 = numberInstructions();
    a_d = 10.0;
    b_d = 2.0;
    c_d = 0;
    int counter = 0;
    for(int i = 0; i < 100000; i++){
        a_d /= 0.99999;
        b_d /= 0.99997;
        c_d += (a_d / b_d);
        tempCycles = cycleCount();
        tempLSU = m33_hw->dwt_lsucnt;
        tempCPI = CPICNT_Val();
        tempEXC = m33_hw->dwt_exccnt;
        tempSLEEP = SLEEPCNT_Val();
        tempFOLD = m33_hw->dwt_foldcnt;
        //printf("Cycle count on %i is %llu\n", i, tempCycles);
        //printf("LSU count on %i is %llu\n", i, tempLSU);
        if (tempCycles < prevTempCycles) {
            //printf("Cycle count has overflowed\n");
            instruction_overflows++;
        }
        if (tempLSU < prevTempLSU) {
            lsu_overflows++;
        }
        if (tempCPI < prevTempCPI) {
            cpi_overflows++;
        }
        if (tempEXC < prevTempEXC) {
            exc_overflows++;
        }
        if (tempSLEEP < prevTempSLEEP) {
            sleep_overflows++;
        }
        if (tempFOLD < prevTempFOLD) {
            fold_overflows++;
        }
        prevTempCycles = tempCycles; // Update prevTempCycles for the next iteration
        prevTempLSU = tempLSU;
        prevTempCPI = tempCPI;
        prevTempEXC = tempEXC;
        prevTempSLEEP = tempSLEEP;
        prevTempFOLD = tempFOLD;
    }
    time2 =time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();
    printf("C = %lf\n", c_d); //Testing printing just the final result to make sure compiler still doesn't optimize
    printf("Double Division Results: \n");
    printf("Time taken: %.4f ms\n", (float)(time2 - time1) / 1000);
    printf("Instructions executed: %llu\n", instructions2-instructions1);
    printf("Clock cycles: %llu\n", cycles2-cycles1);
    printf("Instruction Overflows: %i\n", instruction_overflows);
    printf("LSU Overflows: %i\n", lsu_overflows);
    printf("CPI Overflows: %i\n", cpi_overflows);
    printf("EXC Overflows: %i\n", exc_overflows);
    printf("SLEEP Overflows: %i\n", sleep_overflows);
    printf("FOLD Overflows: %i\n", fold_overflows);

    //Put this at the end of all benchmarks to help the data collector
    printf("\nEnd of benchmark\n");
    sleep_ms(50);
    stopBenchmark();
    //Put this at the end because picotool doesn't like connecting after main finishes
    while(true);
}

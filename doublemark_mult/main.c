#include <stdio.h>
#include <math.h>
#include "hardware/structs/otp.h"
#include "pico/stdlib.h"
#include "instruction_count.h"
#include "power_functions.h"

/* The printf's may be removed to isolate just the math calculations */

int main(void) {

    stdio_init_all();
    //sleep_ms(5000);
    printf("Hello Doublemark Mult!\n");

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
    printf("Double multiplication.\n");
    startPowerTesting();
    time1 = time_us_64();
    cycles1 = cycleCount();
    instructions1 = numberInstructions();
    a_d = 1.0;
    b_d = 1.04;
    c_d = 0;
    for(int i = 0; i < 100000; i++){
        a_d *= 1.00001;
        b_d *= 1.00003;
        c_d += (a_d * b_d);
        //printf("C = %f\n", c_d);
        //Without the print statement, it takes a very small amount of time/instructions to execute
        //Might want to figure out a way to not have the compiler optimize this away.
    }
    time2 =time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();
    printf("C = %f\n", c_d); //Testing printing just the final result to make sure compiler still doesn't optimize
    printf("Double Multiplication Results: \n");
    printf("Time taken: %.4f ms\n", (float)(time2 - time1) / 1000);
    printf("Instructions executed: %llu\n", instructions2-instructions1);
    printf("Clock cycles: %llu\n", cycles2-cycles1);

    //Put this at the end of all benchmarks to help the data collector
    printf("\nEnd of benchmark\n");
    sleep_ms(50);
    stopBenchmark();
    //Put this at the end because picotool doesn't like connecting after main finishes
    while(true);
}

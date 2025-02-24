#include <stdio.h>
#include "hardware/structs/otp.h"
#include "pico/stdlib.h"
#include "instruction_count.h"
#include "power_functions.h"

/* The printf's may be removed to isolate just the math calculations */

int main(void) {

    stdio_init_all();
    sleep_ms(5000);
    printf("Hello Floatmark!\n");

    //Used to confirm which arch is running
    uint32_t archReg = otp_hw->archsel_status;
    bool arch = (archReg & 0x1); //0 is arm and 1 is risc-v
    switch(arch){
        case 0:
            printf("Hello from ARM!\n");
            break;
        case 1:
            printf("Hello from RISC-V!\n");
            break;
    }

    initPowerTesting();
    enableClockCount();

    //Variables used for testing operations. _f means float and _d means double
    float a_f, b_f, c_f;
    double a_d, b_d, c_d;

    //Variables used to capture times
    uint64_t instructions1, instructions2;
    uint64_t cycles1, cycles2;
    uint64_t time1, time2;

    printf("\n");
    printf("Floating addition.\n");
    startPowerTesting();
    time1 = time_us_64();
    cycles1 = cycleCount();
    instructions1 = numberInstructions();
    a_f = 0.0f;
    b_f = 5.0f;
    c_f = 0;
    for(int i = 0; i<100; i++){
        a_f+=0.5f;
        b_f += 5.3f;
        c_f = a_f+b_f;
        //printf("C = %f\n", c_f);
        //Without the print statement, it takes a very small amount of time/instructions to execute
        //Might want to figure out a way to not have the compiler optimize this away.
    }
    time2 =time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();
    printf("C = %f\n", c_f); //Testing printing just the final result to make sure compiler still doesn't optimize
    printf("Float Addition Results: \n");
    printf("Time taken: %.4f ms\n", (float)(time2 - time1) / 1000);
    printf("Instructions executed: %llu\n", instructions2-instructions1);
    printf("Clock cycles: %llu\n", cycles2-cycles1);

    //Making sure that the different tests show up in the power profiler
    sleep_ms(500);

    printf("\n");
    printf("Floating subtraction.\n");
    startPowerTesting();
    time1 = time_us_64();
    cycles1 = cycleCount();
    instructions1 = numberInstructions();
    a_f = 0.0f;
    b_f = 5.0f;
    c_f = 0;
    for(int i = 0; i<100; i++){
        a_f-=0.5f;
        b_f -= 5.3f;
        c_f = a_f-b_f;
        //printf("C = %f\n", c_f);
        //Without the print statement, it takes a very small amount of time/instructions to execute
        //Might want to figure out a way to not have the compiler optimize this away.
    }
    time2 =time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();
    printf("C = %f\n", c_f); //Testing printing just the final result to make sure compiler still doesn't optimize
    printf("Float Subtraction Results: \n");
    printf("Time taken: %.4f ms\n", (float)(time2 - time1) / 1000);
    printf("Instructions executed: %llu\n", instructions2-instructions1);
    printf("Clock cycles: %llu\n", cycles2-cycles1);

    //Making sure that the different tests show up in the power profiler
    sleep_ms(500);

    printf("\n");
    printf("Floating multiplication.\n");
    startPowerTesting();
    time1 = time_us_64();
    cycles1 = cycleCount();
    instructions1 = numberInstructions();
    a_f = 1.0f;
    b_f = 2.0f;
    c_f = 0;
    for(int i = 0; i < 100; i++){
        a_f *= 1.01f;
        b_f *= 1.03f;
        c_f = a_f * b_f;
        //printf("C = %f\n", c_f);
        //Without the print statement, it takes a very small amount of time/instructions to execute
        //Might want to figure out a way to not have the compiler optimize this away.
    }
    time2 =time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();
    printf("C = %f\n", c_f); //Testing printing just the final result to make sure compiler still doesn't optimize
    printf("Float Multiplication Results: \n");
    printf("Time taken: %.4f ms\n", (float)(time2 - time1) / 1000);
    printf("Instructions executed: %llu\n", instructions2-instructions1);
    printf("Clock cycles: %llu\n", cycles2-cycles1);

    //Making sure that the different tests show up in the power profiler
    sleep_ms(500);

    printf("\n");
    printf("Floating division.\n");
    startPowerTesting();
    time1 = time_us_64();
    cycles1 = cycleCount();
    instructions1 = numberInstructions();
    a_f = 10.0f;
    b_f = 2.0f;
    c_f = 0;
    for(int i = 0; i < 100; i++){
        a_f /= 1.1f;
        b_f /= 1.05f;
        c_f = a_f / b_f;
        //printf("C = %f\n", c_f);
        //Without the print statement, it takes a very small amount of time/instructions to execute
        //Might want to figure out a way to not have the compiler optimize this away.
    }
    time2 =time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();
    printf("C = %f\n", c_f); //Testing printing just the final result to make sure compiler still doesn't optimize
    printf("Float Multiplication Results: \n");
    printf("Time taken: %.4f ms\n", (float)(time2 - time1) / 1000);
    printf("Instructions executed: %llu\n", instructions2-instructions1);
    printf("Clock cycles: %llu\n", cycles2-cycles1);

    //Put this at the end because picotool doesn't like connecting after main finishes
    while(true);
}

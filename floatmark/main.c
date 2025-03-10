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
    printf("Hello Floatmark!\n");

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
    for(int i = 0; i<100000; i++){
        a_f+=0.5f;
        b_f += 0.3f;
        c_f += a_f+b_f-10;
        //printf("C = %f\n", c_f);
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
    for(int i = 0; i<100000; i++){
        a_f-=0.5f;
        b_f -= 0.3f;
        c_f -= a_f-b_f+10;
        //printf("C = %f\n", c_f);
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
    b_f = 1.04f;
    c_f = 0;
    for(int i = 0; i < 100000; i++){
        a_f *= 1.00001f;
        b_f *= 1.00003f;
        c_f += (a_f * b_f);
        //printf("C = %f\n", c_f);
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
    //Pick a number above 1 for one , and below 1 for another so that one increases and the other decreases
    for(int i = 0; i < 100000; i++){
        a_f /= 0.99999f;
        b_f /= 0.99997f;
        c_f += (a_f / b_f);
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

    //Begin double section

    printf("\nStarting DoubleMark\n");

    printf("\n");
    printf("Double addition.\n");
    startPowerTesting();
    time1 = time_us_64();
    cycles1 = cycleCount();
    instructions1 = numberInstructions();
    a_d = 0.0;
    b_d = 5.0;
    c_d = 0;
    for(int i = 0; i<100000; i++){
        a_d+=0.5;
        b_d += 0.3;
        c_d += a_d+b_d-10;
        //printf("C = %f\n", c_f);
    }
    time2 =time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();
    printf("C = %f\n", c_d); //Testing printing just the final result to make sure compiler still doesn't optimize
    printf("Double Addition Results: \n");
    printf("Time taken: %.4f ms\n", (float)(time2 - time1) / 1000);
    printf("Instructions executed: %llu\n", instructions2-instructions1);
    printf("Clock cycles: %llu\n", cycles2-cycles1);

    //Making sure that the different tests show up in the power profiler
    sleep_ms(500);

    printf("\n");
    printf("Double subtraction.\n");
    startPowerTesting();
    time1 = time_us_64();
    cycles1 = cycleCount();
    instructions1 = numberInstructions();
    a_d = 0.0;
    b_d = 5.0;
    c_d = 0;
    for(int i = 0; i<100000; i++){
        a_d-=0.5;
        b_d -= 0.3;
        c_d -= a_d-b_d+10;
        //printf("C = %f\n", c_d);
    }
    time2 =time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();
    printf("C = %f\n", c_d); //Testing printing just the final result to make sure compiler still doesn't optimize
    printf("Double Subtraction Results: \n");
    printf("Time taken: %.4f ms\n", (float)(time2 - time1) / 1000);
    printf("Instructions executed: %llu\n", instructions2-instructions1);
    printf("Clock cycles: %llu\n", cycles2-cycles1);

    //Making sure that the different tests show up in the power profiler
    sleep_ms(500);

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

    //Making sure that the different tests show up in the power profiler
    sleep_ms(500);

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

    //Put this at the end because picotool doesn't like connecting after main finishes
    while(true);
}

#include "snipmath.h"
#include <math.h>
#include <stdio.h>
#include "hardware/structs/otp.h"
#include "pico/stdlib.h"
#include "powman_example.h"
#include "instruction_count.h"

//Used to find instruction count
/*#if PICO_PLATFORM==rp2350-riscv
#include "hardware/regs/rvcsr.h"

void enable_instruction_counting();
uint32_t read_instructions();

#endif*/

/* The printf's may be removed to isolate just the math calculations */

int main(void) {

    stdio_init_all();
    double a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
    double a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
    double a3 = 1.0, b3 = -3.5, c3 = 22.0, d3 = -31.0;
    double a4 = 1.0, b4 = -13.7, c4 = 1.0, d4 = -35.0;
    double x[3];
    double X;
    int solutions;
    int i;
    unsigned long l = 0x3fed0169L;
    struct int_sqrt q;
    long n = 0;

    uint32_t archReg = otp_hw->archsel_status;
    bool arch = (archReg & 0x1); //0 is arm and 1 is risc-v

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    if(arch){
        gpio_put(LED_PIN, 1);
    }


    /*//Testing the instruction counter (RISC only)
    #if PICO_PLATFORM==rp2350-riscv
    printf("Hello from RISC-V\n");
    int temp = 0;
    enable_instruction_counting();
    uint32_t instructions = read_instructions();
    printf("%lu\n", instructions);
    temp++;
    instructions = read_instructions();
    printf("%lu\n", instructions);
    //while(1){

    //}

    #endif*/

    //Enabling the clock counter on the ARM cores
    #if PICO_PLATFORM==rp2350
        enableClockCount();
        printf("%lu\n", cycleCount());
    #endif

    uint64_t endTime;
    uint64_t startTime = time_us_64();

    /*
    *//* solve soem cubic functions *//*
    printf("********* CUBIC FUNCTIONS ***********\n");
    *//* should get 3 solutions: 2, 6 & 2.5   *//*
    SolveCubic(a1, b1, c1, d1, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");
    *//* should get 1 solution: 2.5           *//*
    SolveCubic(a2, b2, c2, d2, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");
    SolveCubic(a3, b3, c3, d3, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");
    SolveCubic(a4, b4, c4, d4, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");
    *//* Now solve some random equations *//*
    for (a1 = 1; a1 < 10; a1++) {
        for (b1 = 10; b1 > 0; b1--) {
            for (c1 = 5; c1 < 15; c1 += 0.5) {
                for (d1 = -1; d1 > -11; d1--) {
                    SolveCubic(a1, b1, c1, d1, &solutions, x);
                    printf("Solutions:");
                    for (i = 0; i < solutions; i++)
                        printf(" %f", x[i]);
                    printf("\n");
                }
            }
        }
    }

    printf("********* INTEGER SQR ROOTS ***********\n");
    *//* perform some integer square roots *//*
    for (i = 0; i < 1001; ++i) {
        usqrt(i, &q);
        // remainder differs on some machines
        // printf("sqrt(%3d) = %2d, remainder = %2d\n",
        printf("sqrt(%3d) = %2d\n",
               i, q.sqrt);
    }
    usqrt(l, &q);
    //printf("\nsqrt(%lX) = %X, remainder = %X\n", l, q.sqrt, q.frac);
    printf("\nsqrt(%lX) = %X\n", l, q.sqrt);


    printf("********* ANGLE CONVERSION ***********\n");
    *//* convert some rads to degrees *//*
    for (X = 0.0; X <= 360.0; X += 1.0)
        printf("%3.0f degrees = %.12f radians\n", X, deg2rad(X));
    puts("");
    for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 180))
        printf("%.12f radians = %3.0f degrees\n", X, rad2deg(X));
    */
    endTime = time_us_64();

    printf("Time taken: %lld us\n", endTime - startTime);

#if PICO_PLATFORM==rp2350
    uint32_t clockCyclesPre = cycleCount();
    int tempAdd = 0;
    tempAdd ++;
    uint32_t clockCyclesPost = cycleCount();
    printf("Clock cycles before add: %lu\n", clockCyclesPre);
    printf("Clock cycles after add: %lu\n", clockCyclesPost);
#endif

    powman_example_off_until_gpio_high(PICO_DEFAULT_LED_PIN);
}


/*
// Function to enable instruction counting
void enable_instruction_counting() {
    // Assuming mcountinhibit is at offset 0x320
    uint32_t *mcountinhibit = (uint32_t *)RVCSR_MCOUNTINHIBIT_OFFSET;
    *mcountinhibit &= ~(1 << RVCSR_MCOUNTINHIBIT_IR_LSB); // Clear the `IR` bit to enable instruction counting
}

// Function to read the value from the MINSTRETH register
uint32_t read_instructions() {
    uint32_t *minstreth = (uint32_t *)RVCSR_MINSTRETH_OFFSET;
    return *minstreth;
}*/

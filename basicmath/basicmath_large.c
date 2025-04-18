#include "snipmath.h"
#include <math.h>
#include "stdio.h"
#include "hardware/structs/otp.h"
#include "pico/stdlib.h"
#include "power_functions.h"
#include "instruction_count.h"

/* The printf's may be removed to isolate just the math calculations */

int main(void) {
    stdio_init_all();
    printf("Starting Basicmath Large\n");
    double a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
    double x[3];
    double X;
    int solutions;
    int i;
    unsigned long l = 0x3fed0169L;
    struct int_sqrt q;
    long n = 0;

   uint32_t archReg = otp_hw->archsel_status;
    bool arch = (archReg & 0x1); //0 is arm and 1 is risc-v
    if (arch) {
        printf("Hello from RISC-V!\n");
    } else {
        printf("Hello from ARM!\n");
    }

    initPowerTesting();
    enableClockCount();

    uint64_t time1, time2;
    uint64_t cycles1, cycles2;
    uint64_t instructions1, instructions2;

    startBenchmark();
    sleep_ms(50);

    startPowerTesting();
    time1 = time_us_64();
    cycles1 = cycleCount();
    instructions1 = numberInstructions();

    /* solve soem cubic functions */
    printf("********* CUBIC FUNCTIONS ***********\n");
    /* should get 3 solutions: 2, 6 & 2.5   */
    SolveCubic(a1, b1, c1, d1, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");

    a1 = 1.0;
    b1 = -4.5;
    c1 = 17.0;
    d1 = -30.0;
    /* should get 1 solution: 2.5           */
    SolveCubic(a1, b1, c1, d1, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");

    a1 = 1.0;
    b1 = -3.5;
    c1 = 22.0;
    d1 = -31.0;
    SolveCubic(a1, b1, c1, d1, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");

    a1 = 1.0;
    b1 = -13.7;
    c1 = 1.0;
    d1 = -35.0;
    SolveCubic(a1, b1, c1, d1, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");

    a1 = 3.0;
    b1 = 12.34;
    c1 = 5.0;
    d1 = 12.0;
    SolveCubic(a1, b1, c1, d1, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");

    a1 = -8.0;
    b1 = -67.89;
    c1 = 6.0;
    d1 = -23.6;
    SolveCubic(a1, b1, c1, d1, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");

    a1 = 45.0;
    b1 = 8.67;
    c1 = 7.5;
    d1 = 34.0;
    SolveCubic(a1, b1, c1, d1, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");

    a1 = -12.0;
    b1 = -1.7;
    c1 = 5.3;
    d1 = 16.0;
    SolveCubic(a1, b1, c1, d1, &solutions, x);
    printf("Solutions:");
    for (i = 0; i < solutions; i++)
        printf(" %f", x[i]);
    printf("\n");

    /* Now solve some random equations */
    for (a1 = 1; a1 < 10; a1 += 1) {
        for (b1 = 10; b1 > 0; b1 -= .25) {
            for (c1 = 5; c1 < 15; c1 += 0.61) {
                for (d1 = -1; d1 > -5; d1 -= .451) {
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
    /* perform some integer square roots */
    for (i = 0; i < 100000; i += 2) {
        usqrt(i, &q);
        // remainder differs on some machines
        // printf("sqrt(%3d) = %2d, remainder = %2d\n",
        printf("sqrt(%3d) = %2d\n",
               i, q.sqrt);
    }
    printf("\n");
    for (l = 0x3fed0169L; l < 0x3fed4169L; l++) {
        usqrt(l, &q);
        //printf("\nsqrt(%lX) = %X, remainder = %X\n", l, q.sqrt, q.frac);
        printf("sqrt(%lX) = %X\n", l, q.sqrt);
    }


    printf("********* ANGLE CONVERSION ***********\n");
    /* convert some rads to degrees */
/*   for (X = 0.0; X <= 360.0; X += 1.0) */
    for (X = 0.0; X <= 360.0; X += .001)
        printf("%3.0f degrees = %.12f radians\n", X, deg2rad(X));
    puts("");
/*   for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 180)) */
    for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 5760))
        printf("%.12f radians = %3.0f degrees\n", X, rad2deg(X));

    time2 = time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();

    printf("Basicmath large results: \n");
    printf("Time taken: %.4f ms\n", (float)(time2 - time1) / 1000);
    printf("Instructions executed: %llu\n", instructions2 - instructions1);
    printf("Clock cycles: %llu\n", cycles2 - cycles1);


    //Put this at the end of all benchmarks to help the data collector
    printf("\nEnd of benchmark\n");
    sleep_ms(50);
    stopBenchmark();
    //Put this at the end because picotool doesn't like connecting after main finishes
    while(true);
}

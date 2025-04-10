#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/structs/otp.h"
#include "instruction_count.h"
#include "power_functions.h"

#define UNLIMIT
#define MAXARRAY 60000 /* this number, if too large, will cause a seg. fault!! */

struct my3DVertexStruct {
    int x, y, z;
    double distance;
};

int compare(const void *elem1, const void *elem2) {
    /* D = [(x1 - x2)^2 + (y1 - y2)^2 + (z1 - z2)^2]^(1/2) */
    /* sort based on distances from the origin... */

    double distance1, distance2;

    distance1 = (*((struct my3DVertexStruct *) elem1)).distance;
    distance2 = (*((struct my3DVertexStruct *) elem2)).distance;

    return (distance1 > distance2) ? 1 : ((distance1 == distance2) ? 0 : -1);
}


int main(int argc, char *argv[]) {
    stdio_init_all();
    printf("Hello, world!\n");
    struct my3DVertexStruct array[MAXARRAY];
    FILE *fp;
    int i, count = 0;
    int x, y, z;
    argc = 3

    if (argc < 2) {
        fprintf(stderr, "Usage: qsort_large <file>\n");
        exit(-1);
    } else {
        fp = fopen(argv[1], "r");

        while ((fscanf(fp, "%d", &x) == 1) && (fscanf(fp, "%d", &y) == 1) && (fscanf(fp, "%d", &z) == 1) &&
               (count < MAXARRAY)) {
            array[count].x = x;
            array[count].y = y;
            array[count].z = z;
            array[count].distance = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
            count++;
        }
    }

    printf("Starting Qsort Large\n");
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

    printf("\nSorting %d vectors based on distance from the origin.\n\n", count);
    qsort(array, count, sizeof(struct my3DVertexStruct), compare);

    for (i = 0; i < count; i++)
        printf("%d %d %d\n", array[i].x, array[i].y, array[i].z);


    time2 = time_us_64();
    cycles2 = cycleCount();
    instructions2 = numberInstructions();
    stopPowerTesting();

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

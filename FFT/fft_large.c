#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hardware/structs/otp.h"
#include "pico/stdlib.h"
#include "fourier.h"
#include "instruction_count.h"
#include "power_functions.h"

int main() {

    stdio_init_all();
    unsigned MAXSIZE;
    unsigned MAXWAVES;
    unsigned i,j;
    float *RealIn;
    float *ImagIn;
    float *RealOut;
    float *ImagOut;
    float *coeff;
    float *amp;
    int invfft=0;
    int argc = 4;
    char *argv[] = {"", "8", "32768", ""};

    if (argc<3)
    {
        printf("Usage: fft <waves> <length> -i\n");
        printf("-i performs an inverse fft\n");
        printf("make <waves> random sinusoids");
        printf("<length> is the number of samples\n");
        exit(-1);
    }
    else if (argc==4)
        invfft = !strncmp(argv[3],"-i",2);
    MAXSIZE=atoi(argv[2]);
    MAXWAVES=atoi(argv[1]);

    srand(1);

    RealIn=(float*)malloc(sizeof(float)*MAXSIZE);
    ImagIn=(float*)malloc(sizeof(float)*MAXSIZE);
    RealOut=(float*)malloc(sizeof(float)*MAXSIZE);
    ImagOut=(float*)malloc(sizeof(float)*MAXSIZE);
    coeff=(float*)malloc(sizeof(float)*MAXWAVES);
    amp=(float*)malloc(sizeof(float)*MAXWAVES);

    /* Makes MAXWAVES waves of random amplitude and period */
    for(i=0;i<MAXWAVES;i++)
    {
        coeff[i] = rand()%1000;
        amp[i] = rand()%1000;
    }
    for(i=0;i<MAXSIZE;i++)
    {
        /*   RealIn[i]=rand();*/
        RealIn[i]=0;
        for(j=0;j<MAXWAVES;j++)
        {
            /* randomly select sin or cos */
            if (rand()%2)
            {
                RealIn[i]+=coeff[j]*cos(amp[j]*i);
            }
            else
            {
                RealIn[i]+=coeff[j]*sin(amp[j]*i);
            }
            ImagIn[i]=0;
        }
    }

   printf("Starting FFT Large\n");
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

    /* regular*/
    fft_float (MAXSIZE,invfft,RealIn,ImagIn,RealOut,ImagOut);

    printf("RealOut:\n");
    for (i=0;i<MAXSIZE;i++)
        printf("%f \t", RealOut[i]);
    printf("\n");

    printf("ImagOut:\n");
    for (i=0;i<MAXSIZE;i++)
        printf("%f \t", ImagOut[i]);
    printf("\n");

    free(RealIn);
    free(ImagIn);
    free(RealOut);
    free(ImagOut);
    free(coeff);
    free(amp);

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

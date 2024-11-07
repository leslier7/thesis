#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hardware/structs/otp.h"
#include "pico/stdlib.h"
#include "powman_example.h"
#include "fourier.h"

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
    char *argv[] = {"", "8", "32768", "-i"};

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

    uint64_t startTime = time_us_64();
    uint64_t endTime;

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

    endTime = time_us_64();

    printf("Time taken: %lld us\n", endTime - startTime);

    exit(0);


}

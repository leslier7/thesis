#include <stdio.h>
#include "hardware/structs/otp.h"
#include "pico/stdlib.h"
#include "powman_example.h"
#include "instruction_count.h"

/* The printf's may be removed to isolate just the math calculations */

int main(void) {

    stdio_init_all();
    sleep_ms(10000);
    printf("Hello featureTest!\n");

    uint32_t archReg = otp_hw->archsel_status;
    bool arch = (archReg & 0x1); //0 is arm and 1 is risc-v

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    if(arch){
        gpio_put(LED_PIN, 1);
    }


    //Used to tell the power profiler when to start and stop
    const uint ON_PIN = 16;
    gpio_init(ON_PIN);
    gpio_set_dir(ON_PIN, GPIO_OUT);
    gpio_put(ON_PIN, 0);

//    while(true){
//        printf("Turning on pins!\n");
//        gpio_put(ON_PIN, 1);
//        gpio_put(OFF_PIN, 1);
//        sleep_ms(5000);
//        printf("Turning off pins!\n");
//        gpio_put(ON_PIN, 0);
//        gpio_put(OFF_PIN, 0);
//        sleep_ms(5000);
//
//    }

    // Starting the "test"
    gpio_put(ON_PIN, 1);
    int test = 0;
    while(test < 1000){
        test++;
    }
    sleep_ms(5000);
    printf("Finished the test! The value of test is %d\n", test);
    gpio_put(ON_PIN, 0);


    //Testing the instruction counter (RISC only)
    #if ARCH_RISC
    printf("Hello from RISC-V\n");
    int temp = 0;
    enableClockCount();
    uint32_t instructions = numberInstructions();
    for(int i = 0; i< 3; i++){ //Making sure that at least on of the adds has time to retire for risc
        temp++;
    }
    uint32_t instructions2 = numberInstructions();
    printf("Instructions first value: %lu\n", instructions);
    printf("Instructions second value: %lu\n", instructions2);
    printf("Instructions executed: %lu\n", instructions2 - instructions);
    printf("Temp value: %d\n", temp);

    #endif

    //Enabling the clock counter on the ARM cores
    // Enabling the clock counter on the ARM cores
#if ARCH_ARM
//    enableClockCount();
//    uint32_t structCount = cycleCount();
//    printf("Clock cycles from struct: %lu\n", structCount);
#elif ARCH_RISC
    // enableClockCount();
    printf("Risc-V\n");
    cycleCount();
#endif

    //uint64_t endTime;
    //uint64_t startTime = time_us_64();


    //endTime = time_us_64();

    //printf("Time taken: %lld us\n", endTime - startTime);


//    uint32_t clockCyclesPre = cycleCount();
//    printf("Right before instructions");
//    uint32_t instructionsPre = numberInstructions();
//    int tempAdd = 0;
//    tempAdd ++;
//    uint32_t clockCyclesPost = cycleCount();
//    uint32_t instructionsPost = numberInstructions();
//    printf("Clock cycles before add: %lu\n", clockCyclesPre);
//    printf("Clock cycles after add: %lu\n", clockCyclesPost);
//    printf("Instructions before add: %lu\n", instructionsPre);
//    printf("Instructions after add: %lu\n", instructionsPost);
//    printf("Total instructions between add: %lu\n", (instructionsPost - instructionsPre));


    //powman_example_off_until_gpio_high(PICO_DEFAULT_LED_PIN);
}

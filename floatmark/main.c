#include <stdio.h>
#include "hardware/structs/otp.h"
#include "pico/stdlib.h"
#include "instruction_count.h"
#include "power_functions.h"

/* The printf's may be removed to isolate just the math calculations */

int main(void) {

    stdio_init_all();
    sleep_ms(10000);
    printf("Hello Floatmark!\n");

    uint32_t archReg = otp_hw->archsel_status;
    bool arch = (archReg & 0x1); //0 is arm and 1 is risc-v



//Put this at the end because picotool doesn't like connecting after main finishes
while(true);


}

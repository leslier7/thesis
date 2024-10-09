/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/structs/pio.h"
#include "hardware/structs/otp.h"
#include <stdio.h>

#define ARCHSEL_STATUS 0x15c


int main() {

    stdio_init_all();

    //Check the architecture of the RP2350
    //uint32_t archReg = *(volatile uint32_t *)(OTP_BASE + ARCHSEL_STATUS);
    uint32_t archReg = otp_hw->archsel_status;
    bool arch = (archReg & 0x1); //0 is arm and 1 is risc-v

    if(arch){
        printf("Hello World from RISC-V\n");
    } else {
        printf("Hello World from ARM\n");
    }

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {

        if(!arch){ //arm
            gpio_put(LED_PIN, 1);
            sleep_ms(1000);
            gpio_put(LED_PIN, 0);
            sleep_ms(1000);
            gpio_put(LED_PIN, 1);
            sleep_ms(1000);
            gpio_put(LED_PIN, 0);
            sleep_ms(1000);
            gpio_put(LED_PIN, 1);
            sleep_ms(1000);
            gpio_put(LED_PIN, 0);
            sleep_ms(2500);
        } else { //risc-v
            gpio_put(LED_PIN, 1);
            sleep_ms(100);
            gpio_put(LED_PIN, 0);
            sleep_ms(100);
            gpio_put(LED_PIN, 1);
            sleep_ms(100);
            gpio_put(LED_PIN, 0);
            sleep_ms(100);
            gpio_put(LED_PIN, 1);
            sleep_ms(100);
            gpio_put(LED_PIN, 0);
            sleep_ms(250);
        }
    }
}

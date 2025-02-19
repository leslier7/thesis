//
// Created by Robbie on 2/19/25.
//

#include "power_functions.h"
#include "pico/stdlib.h"

//Used to tell the power profiler when to start and stop
#define ON_PIN 16

void initPowerTesting(){
    gpio_init(ON_PIN);
    gpio_set_dir(ON_PIN, GPIO_OUT);
    gpio_put(ON_PIN, 0);
}

inline void startTesting(){
    gpio_put(ON_PIN, 0);
}

inline void stopTesting(){
    gpio_put(ON_PIN, 0);
}
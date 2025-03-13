//
// Created by Robbie on 2/19/25.
//

#include "power_functions.h"
#include "pico/stdlib.h"

//Used to tell the power profiler when to start and stop
#define ON_PIN 16
#define BENCHMARK_PIN 17

void initPowerTesting(){
    gpio_init(ON_PIN);
    gpio_set_dir(ON_PIN, GPIO_OUT);
    gpio_put(ON_PIN, 0);
    gpio_init(BENCHMARK_PIN);
    gpio_set_dir(BENCHMARK_PIN, GPIO_OUT);
    gpio_put(BENCHMARK_PIN, 0);
}

void startPowerTesting(){
    gpio_put(ON_PIN, 1);
}

void stopPowerTesting(){
    gpio_put(ON_PIN, 0);
}

void startBenchmark(){
    gpio_put(BENCHMARK_PIN, 1);
}

void stopBenchmark(){
    gpio_put(BENCHMARK_PIN, 0);
}
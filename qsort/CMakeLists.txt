cmake_minimum_required(VERSION 3.13)

set(NAME qsort)
set(PICO_BOARD pico2)
#set(PICO_PLATFORM rp2350)


include(pico_sdk_import.cmake)

project(qsort)

pico_sdk_init()

add_executable(qsort_small
        qsort_small.c
        powman_example.c
        )

add_executable(qsort_large
        qsort_large.c
        powman_example.c
)

# pull in common dependencies
target_link_libraries(qsort_small pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)
target_link_libraries(qsort_large pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)

# create map/bin/hex file etc.
pico_add_extra_outputs(qsort_small)
pico_add_extra_outputs(qsort_large)


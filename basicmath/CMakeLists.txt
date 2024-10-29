cmake_minimum_required(VERSION 3.13)

set(NAME basicmath)
set(PICO_BOARD pico2)
#set(PICO_PLATFORM rp2350)


include(pico_sdk_import.cmake)

project(basicmath)

pico_sdk_init()

add_executable(basicmath_small
        basicmath_small.c
        snipmath.h
        round.h
        sniptype.h
        cubic.c
        isqrt.c
        rad2deg.c
        powman_example.c
        )

add_executable(basicmath_large
        basicmath_large.c
        snipmath.h
        round.h
        sniptype.h
        cubic.c
        isqrt.c
        rad2deg.c
        powman_example.c
)

# pull in common dependencies
target_link_libraries(basicmath_small pico_stdlib hardware_powman pico_bootsel_via_double_reset)
target_link_libraries(basicmath_large pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)

# create map/bin/hex file etc.
pico_add_extra_outputs(basicmath_small)
pico_add_extra_outputs(basicmath_large)


cmake_minimum_required(VERSION 3.13)

set(NAME coremark)
set(PICO_BOARD pico2)
#set(PICO_PLATFORM rp2350)


include(pico_sdk_import.cmake)

project(coremark)

pico_sdk_init()

add_executable(coremark
        core_portme.c
        core_portme.h
        core_main.c
        core_matrix.c
        core_list_join.c
        core_state.c
        core_util.c
        #cvt.c
        #ee_printf.c
        coremark.h
)


# pull in common dependencies
target_link_libraries(coremark pico_stdlib hardware_powman pico_bootsel_via_double_reset)

# create map/bin/hex file etc.
pico_add_extra_outputs(coremark)



cmake_minimum_required(VERSION 3.13)

set(NAME bitcnts)
set(PICO_BOARD pico2)
#set(PICO_PLATFORM rp2350)


include(pico_sdk_import.cmake)

project(bitcnts)

pico_sdk_init()

add_executable(bitcnts_small
        bitcnts_small.c
        bitarray.c
        bitcnt_1.c
        bitcnt_2.c
        bitcnt_3.c
        bitcnt_4.c
        bitfiles.c
        bitops.h
        bitstrng.c
        bstr_i.c
        conio.h
        extkword.h
        sniptype.h
        )

add_executable(bitcnts_large
        bitcnts_large.c
        bitarray.c
        bitcnt_1.c
        bitcnt_2.c
        bitcnt_3.c
        bitcnt_4.c
        bitfiles.c
        bitops.h
        bitstrng.c
        bstr_i.c
        conio.h
        extkword.h
        sniptype.h
)

# pull in common dependencies
target_link_libraries(bitcnts_small pico_stdlib hardware_structs pico_bootsel_via_double_reset)
target_link_libraries(bitcnts_large pico_stdlib hardware_structs pico_bootsel_via_double_reset)

# create map/bin/hex file etc.
pico_add_extra_outputs(bitcnts_small)
pico_add_extra_outputs(bitcnts_large)


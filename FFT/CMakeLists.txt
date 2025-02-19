cmake_minimum_required(VERSION 3.13)

set(NAME FFT)
set(PICO_BOARD pico2)
#set(PICO_PLATFORM rp2350)


include(pico_sdk_import.cmake)

project(FFT)

pico_sdk_init()

add_executable(fft_small
        fft_small.c
        powman_example.c
        fftmisc.c
        ddc.h
        ddcmath.h
        fourier.h
        fourierf.c
        )

add_executable(fft_small_i
        fft_small_i.c
        powman_example.c
        fftmisc.c
        ddc.h
        ddcmath.h
        fourier.h
        fourierf.c
)

add_executable(fft_large
        fft_large.c
        powman_example.c
        fftmisc.c
        ddc.h
        ddcmath.h
        fourier.h
        fourierf.c
)

add_executable(fft_large_i
        fft_large_i.c
        powman_example.c
        fftmisc.c
        ddc.h
        ddcmath.h
        fourier.h
        fourierf.c
)

# pull in common dependencies
target_link_libraries(fft_small pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)
target_link_libraries(fft_large pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)
target_link_libraries(fft_small_i pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)
target_link_libraries(fft_large_i pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)

# create map/bin/hex file etc.
pico_add_extra_outputs(fft_small)
pico_add_extra_outputs(fft_large)
pico_add_extra_outputs(fft_small_i)
pico_add_extra_outputs(fft_large_i)


cmake_minimum_required(VERSION 3.13)

set(NAME bitcnts)
set(PICO_BOARD pico2)
#set(PICO_PLATFORM rp2350)

set(ARCH "arm" CACHE STRING "Architecture for the RP2350 (arm or risc)")

if(ARCH STREQUAL "arm")
    message(STATUS "Building for ARM architecture")
    add_definitions(-DARCH_ARM)
elseif(ARCH STREQUAL "risc")
    message(STATUS "Building for RISC architecture")
    add_definitions(-DARCH_RISC)
else()
    message(FATAL_ERROR "Unsupported architecture: ${ARCH}")
endif()

SET(CMAKE_CXX_FLAGS_DEBUG "-O0")
SET(CMAKE_C_FLAGS_DEBUG "-O0")

# Define UART and USB settings
set(UART_ENABLE 1)
set(USB_ENABLE 0)

include(pico_sdk_import.cmake)

project(bitcnts)

pico_sdk_init()

add_executable(bitcnts_small_O3
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
        power_functions.c
        instruction_count.c
        )
target_compile_options(bitcnts_small_O3 PRIVATE -O3)
target_link_libraries(bitcnts_small_O3 pico_stdlib pico_bootsel_via_double_reset)
pico_add_extra_outputs(bitcnts_small_O3)
pico_enable_stdio_usb(bitcnts_small_O3 ${USB_ENABLE})
pico_enable_stdio_uart(bitcnts_small_O3 ${UART_ENABLE})

add_executable(bitcnts_small_O0
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
        power_functions.c
        instruction_count.c
        )
target_compile_options(bitcnts_small_O0 PRIVATE -O0)
target_link_libraries(bitcnts_small_O0 pico_stdlib pico_bootsel_via_double_reset)
pico_add_extra_outputs(bitcnts_small_O0)
pico_enable_stdio_usb(bitcnts_small_O0 ${USB_ENABLE})
pico_enable_stdio_uart(bitcnts_small_O0 ${UART_ENABLE})

add_executable(bitcnts_large_O3
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
        power_functions.c
        instruction_count.c
)
target_compile_options(bitcnts_large_O3 PRIVATE -O3)
target_link_libraries(bitcnts_large_O3 pico_stdlib pico_bootsel_via_double_reset)
pico_add_extra_outputs(bitcnts_large_O3)
pico_enable_stdio_usb(bitcnts_large_O3 ${USB_ENABLE})
pico_enable_stdio_uart(bitcnts_large_O3 ${UART_ENABLE})

add_executable(bitcnts_large_O0
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
        power_functions.c
        instruction_count.c
)
target_compile_options(bitcnts_large_O0 PRIVATE -O0)
target_link_libraries(bitcnts_large_O0 pico_stdlib pico_bootsel_via_double_reset)
pico_add_extra_outputs(bitcnts_large_O0)
pico_enable_stdio_usb(bitcnts_large_O0 ${USB_ENABLE})
pico_enable_stdio_uart(bitcnts_large_O0 ${UART_ENABLE})
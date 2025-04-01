cmake_minimum_required(VERSION 3.13)

set(NAME basicmath)
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

include(pico_sdk_import.cmake)

project(basicmath)

pico_sdk_init()

# Define UART and USB settings
set(UART_ENABLE 1)
set(USB_ENABLE 0)

# Create target with -O3 optimization
add_executable(basicmath_small_O3
        basicmath_small.c
        snipmath.h
        round.h
        sniptype.h
        cubic.c
        isqrt.c
        rad2deg.c
        instruction_count.c
        instruction_count.h
        power_functions.c
)
target_compile_options(basicmath_small_O3 PRIVATE -O3)
target_link_libraries(basicmath_small_O3 pico_stdlib pico_bootsel_via_double_reset)
pico_add_extra_outputs(basicmath_small_O3)
pico_enable_stdio_usb(basicmath_small_O3 ${USB_ENABLE})
pico_enable_stdio_uart(basicmath_small_O3 ${UART_ENABLE})

# Create target with -O0 optimization
add_executable(basicmath_small_O0
        basicmath_small.c
        snipmath.h
        round.h
        sniptype.h
        cubic.c
        isqrt.c
        rad2deg.c
        instruction_count.c
        instruction_count.h
        power_functions.c
)
target_compile_options(basicmath_small_O0 PRIVATE -O0)
target_link_libraries(basicmath_small_O0 pico_stdlib pico_bootsel_via_double_reset)
pico_add_extra_outputs(basicmath_small_O0)
pico_enable_stdio_usb(basicmath_small_O0 ${USB_ENABLE})
pico_enable_stdio_uart(basicmath_small_O0 ${UART_ENABLE})

add_executable(basicmath_large
        basicmath_large.c
        snipmath.h
        round.h
        sniptype.h
        cubic.c
        isqrt.c
        rad2deg.c
        powman_example.c
        instruction_count.c
        instruction_count.h
)

# pull in common dependencies
#target_link_libraries(basicmath_small pico_stdlib hardware_powman pico_bootsel_via_double_reset)
#target_link_libraries(basicmath_large pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)

# create map/bin/hex file etc.
#pico_add_extra_outputs(basicmath_small)
#pico_add_extra_outputs(basicmath_large)


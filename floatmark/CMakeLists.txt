cmake_minimum_required(VERSION 3.13)

set(NAME floatMark)
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

SET(CMAKE_CXX_FLAGS_DEBUG "-O3")
SET(CMAKE_C_FLAGS_DEBUG "-O3")

include(pico_sdk_import.cmake)

project(featureTesting)

pico_sdk_init()

add_executable(main
        main.c
        powman_example.c
        instruction_count.c
        instruction_count.h
        power_functions.c
)

# pull in common dependencies
target_link_libraries(main pico_stdlib hardware_powman pico_bootsel_via_double_reset)


# create map/bin/hex file etc.
pico_add_extra_outputs(main)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
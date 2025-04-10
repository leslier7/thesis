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

include(pico_sdk_import.cmake)

project(featureTesting)

pico_sdk_init()

# Define UART and USB settings
set(UART_ENABLE 1)
set(USB_ENABLE 0)

# Create target with -O3 optimization
add_executable(floatmark_div_O3
        main.c
        instruction_count.c
        instruction_count.h
        power_functions.c
)
target_compile_options(floatmark_div_O3 PRIVATE -O3)
target_link_libraries(floatmark_div_O3 pico_stdlib hardware_powman pico_bootsel_via_double_reset)
pico_add_extra_outputs(floatmark_div_O3)
pico_enable_stdio_usb(floatmark_div_O3 ${USB_ENABLE})
pico_enable_stdio_uart(floatmark_div_O3 ${UART_ENABLE})

# Create target with -O0 optimization
add_executable(floatmark_div_O0
        main.c
        instruction_count.c
        instruction_count.h
        power_functions.c
)
target_compile_options(floatmark_div_O0 PRIVATE -O0)
target_link_libraries(floatmark_div_O0 pico_stdlib hardware_powman pico_bootsel_via_double_reset)
pico_add_extra_outputs(floatmark_div_O0)
pico_enable_stdio_usb(floatmark_div_O0 ${USB_ENABLE})
pico_enable_stdio_uart(floatmark_div_O0 ${UART_ENABLE})
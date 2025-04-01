cmake_minimum_required(VERSION 3.13)

set(NAME qsort)
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

project(qsort)

pico_sdk_init()

add_executable(qsort_small_O3
        qsort_small.c
        powman_example.c
        instruction_count.c
        power_functions.c
        )
target_compile_options(qsort_small_O3 PRIVATE -O3)
target_link_libraries(qsort_small_O3 pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)
pico_add_extra_outputs(qsort_small_O3)
pico_enable_stdio_usb(qsort_small_O3 ${USB_ENABLE})
pico_enable_stdio_uart(qsort_small_O3 ${UART_ENABLE})

add_executable(qsort_small_O0
        qsort_small.c
        powman_example.c
        instruction_count.c
        power_functions.c
        )
target_compile_options(qsort_small_O0 PRIVATE -O0)
target_link_libraries(qsort_small_O0 pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)
pico_add_extra_outputs(qsort_small_O0)
pico_enable_stdio_usb(qsort_small_O0 ${USB_ENABLE})
pico_enable_stdio_uart(qsort_small_O0 ${UART_ENABLE})

# Large
add_executable(qsort_large_O3
        qsort_large.c
        powman_example.c
        instruction_count.c
        power_functions.c
        )
target_compile_options(qsort_large_O3 PRIVATE -O3)
target_link_libraries(qsort_large_O3 pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)
pico_add_extra_outputs(qsort_large_O3)
pico_enable_stdio_usb(qsort_large_O3 ${USB_ENABLE})
pico_enable_stdio_uart(qsort_large_O3 ${UART_ENABLE})

add_executable(qsort_large_O0
        qsort_large.c
        powman_example.c
        instruction_count.c
        power_functions.c
        )
target_compile_options(qsort_large_O0 PRIVATE -O0)
target_link_libraries(qsort_large_O0 pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)
pico_add_extra_outputs(qsort_large_O0)
pico_enable_stdio_usb(qsort_large_O0 ${USB_ENABLE})
pico_enable_stdio_uart(qsort_large_O0 ${UART_ENABLE})
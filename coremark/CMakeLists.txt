cmake_minimum_required(VERSION 3.13)

set(NAME coremark)
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

#SET(CMAKE_CXX_FLAGS_DEBUG "-O0")
#SET(CMAKE_C_FLAGS_DEBUG "-O0")

# Define UART and USB settings
set(UART_ENABLE 1)
set(USB_ENABLE 0)

include(pico_sdk_import.cmake)

project(coremark)

pico_sdk_init()

add_executable(coremark_03
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
        instruction_count.c
        power_functions.c
)
target_compile_options(coremark_03 PRIVATE -O3)
target_link_libraries(coremark_03 pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)
pico_add_extra_outputs(coremark_03)
pico_enable_stdio_usb(coremark_03 ${USB_ENABLE})
pico_enable_stdio_uart(coremark_03 ${UART_ENABLE})

add_executable(coremark_00
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
        instruction_count.c
        power_functions.c
)
target_compile_options(coremark_00 PRIVATE -O0)
target_link_libraries(coremark_00 pico_stdlib hardware_powman hardware_structs pico_bootsel_via_double_reset)
pico_add_extra_outputs(coremark_00)
pico_enable_stdio_usb(coremark_00 ${USB_ENABLE})
pico_enable_stdio_uart(coremark_00 ${UART_ENABLE})
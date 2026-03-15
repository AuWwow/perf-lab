# TargetRP2040.cmake - Configuration for Raspberry Pi Pico (RP2040)

include(FreeRTOSHelpers)

# RP2040 uses ARM_CM0 port
set(FREERTOS_PORT "GCC/ARM_CM0" CACHE STRING "FreeRTOS port for RP2040")

# Pico SDK setup
include(pico_sdk_import.cmake)

# Create executable
add_executable(perf-lab-rp2040
    ${CMAKE_SOURCE_DIR}/src/app/main.c
)

target_link_libraries(perf-lab-rp2040
    PRIVATE
        perf-lab-lib
        freertos_kernel
        pico_stdlib
        hardware_gpio
        hardware_timer
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(perf-lab-rp2040 1)
pico_enable_stdio_uart(perf-lab-rp2040 0)

# Create UF2 file
pico_add_extra_outputs(perf-lab-rp2040)

# Include directories
target_include_directories(perf-lab-rp2040 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
# TargetRenodeSTM32.cmake - Configuration for Renode STM32F4 emulation

include(FreeRTOSHelpers)

# STM32F4 uses ARM_CM4F port
set(FREERTOS_PORT "GCC/ARM_CM4F" CACHE STRING "FreeRTOS port for STM32F4")

# Find ARM GCC toolchain
find_program(ARM_GCC arm-none-eabi-gcc REQUIRED)
find_program(ARM_GXX arm-none-eabi-g++ REQUIRED)
find_program(ARM_OBJCOPY arm-none-eabi-objcopy REQUIRED)

# Set toolchain
set(CMAKE_C_COMPILER ${ARM_GCC})
set(CMAKE_CXX_COMPILER ${ARM_GXX})
set(CMAKE_OBJCOPY ${ARM_OBJCOPY})

# Create executable
add_executable(perf-lab-renode
    ${CMAKE_SOURCE_DIR}/src/app/main.c
)

target_link_libraries(perf-lab-renode
    PRIVATE
        perf-lab-lib
        freertos_kernel
)

# Linker script
set_target_properties(perf-lab-renode PROPERTIES
    LINK_FLAGS "-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
)

# Include directories
target_include_directories(perf-lab-renode PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
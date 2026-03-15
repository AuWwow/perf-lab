# TargetHostSim.cmake - Configuration for POSIX FreeRTOS host simulation
# https://github.com/FreeRTOS/FreeRTOS-Kernel/tree/main/portable/ThirdParty/GCC/Posix

# include(FreeRTOSHelpers)

# Host simulation uses POSIX port
# set(FREERTOS_PORT "GCC/Posix" CACHE STRING "FreeRTOS port for host simulation")

# Find threads for POSIX
find_package(Threads REQUIRED)

# Create executable
add_executable(perf-lab-host-sim
    ${CMAKE_SOURCE_DIR}/src/app/main.c  # Assuming main.c exists in src/app/
)

target_link_libraries(perf-lab-host-sim
    PRIVATE
        perf-lab-lib
        # freertos_kernel
        Threads::Threads
)

# Set output name and directory
set_target_properties(perf-lab-host-sim PROPERTIES
    OUTPUT_NAME "perf-lab"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Include directories for FreeRTOS config
target_include_directories(perf-lab-host-sim PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/targets/host-sim"
)
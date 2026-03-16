# TargetMyRTOS.cmake - Configuration for custom RTOS

# Custom RTOS - no FreeRTOS dependency

# Add kernel
add_subdirectory(${CMAKE_SOURCE_DIR}/src/kernel ${CMAKE_CURRENT_BINARY_DIR}/kernel)

# Create executable
add_executable(perf-lab-my-rtos
    ${CMAKE_SOURCE_DIR}/src/app/main.c
)

target_link_libraries(perf-lab-my-rtos
    PRIVATE
        perf-lab-lib
        kernel-lib
)

# Set output name and directory
set_target_properties(perf-lab-my-rtos PROPERTIES
    OUTPUT_NAME "perf-lab-my-rtos"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Include directories
target_include_directories(perf-lab-my-rtos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
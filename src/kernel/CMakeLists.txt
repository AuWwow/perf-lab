# src/kernel/CMakeLists.txt - Kernel library

add_library(kernel-lib STATIC
    core/core.c
)

target_include_directories(kernel-lib
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/port
)

# Link to common flags
target_link_libraries(kernel-lib PRIVATE common_flags)

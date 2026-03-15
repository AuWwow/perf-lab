
add_executable(linked_list
    linked_list.c
)

target_link_libraries(linked_list PRIVATE perf-lab-lib)

set_target_properties(linked_list PROPERTIES
    OUTPUT_NAME "linked_list"
    SUFFIX ".bin"
)

# Optional: Add optimization flags for benchmarking
if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(linked_list PRIVATE -O3)
endif()

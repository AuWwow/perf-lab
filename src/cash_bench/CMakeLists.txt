
add_executable(perf-lab-bin
    cash_bench.c
)

target_link_libraries(perf-lab-bin PRIVATE perf-lab-lib)

set_target_properties(perf-lab-bin PROPERTIES
    OUTPUT_NAME "perf-lab"
    SUFFIX ".bin"
)

# Optional: Add optimization flags for benchmarking
if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(perf-lab-bin PRIVATE -O3)
endif()


add_executable(cash_bench
    cash_bench.c
)

target_link_libraries(cash_bench PRIVATE perf-lab-lib)

set_target_properties(cash_bench PROPERTIES
    OUTPUT_NAME "cash-bench"
    SUFFIX ".bin"
)

# Optional: Add optimization flags for benchmarking
if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(cash_bench PRIVATE -O3)
endif()

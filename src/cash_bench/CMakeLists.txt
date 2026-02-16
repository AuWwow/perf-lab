

# Add source files
add_executable(perf-lab PRIVATE
        	cash_bench.c 
            )

# Optional: Add optimization flags for benchmarking
if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(perf-lab PRIVATE -O3)
endif()

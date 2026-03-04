
add_executable(sandbox
    sandbox.c
)

target_link_libraries(sandbox PRIVATE perf-lab-lib)

set_target_properties(sandbox PROPERTIES
    OUTPUT_NAME "sandbox"
    SUFFIX ".bin"
)

# Optional: Add optimization flags for benchmarking
if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(sandbox PRIVATE -O3)
endif()

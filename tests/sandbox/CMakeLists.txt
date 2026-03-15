# target_link_libraries(sandbox PRIVATE perf-lab-lib)

add_subdirectory(linked_list)

# Optional: Add optimization flags for benchmarking
# if(CMAKE_BUILD_TYPE MATCHES Release)
#     target_compile_options(sandbox PRIVATE -O3)
# endif()

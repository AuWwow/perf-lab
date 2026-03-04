add_library(perf-lab-lib STATIC)

add_subdirectory(include)

target_link_libraries(perf-lab-lib
    PUBLIC
        allocator-headers
)

add_subdirectory(libs)
add_subdirectory(tests)
# add_subdirectory(memory)
# add_subdirectory(ds)

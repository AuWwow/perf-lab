add_library(perf-lab-lib STATIC)

add_subdirectory(shared/include/allocator)

target_link_libraries(perf-lab-lib
    PUBLIC
        allocator-headers
)

add_subdirectory(shared/libs/allocator)
# add_subdirectory(tests)
# add_subdirectory(memory)
# add_subdirectory(ds)

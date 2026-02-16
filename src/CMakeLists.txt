add_library(perf-lab STATIC)

target_include_directories(perf-lab
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(libs)
# add_subdirectory(memory)
# add_subdirectory(ds)
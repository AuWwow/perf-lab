add_library(allocator-headers INTERFACE)

target_include_directories(allocator-headers
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/..
)

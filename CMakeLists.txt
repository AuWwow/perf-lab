cmake_minimum_required(VERSION 3.16)

project(perf-lab C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Опции сборки
# option(ENABLE_WARNINGS "Enable compiler warnings" ON)
# option(BUILD_TESTS "Build tests" ON)

# Путь к cmake-модулям
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(ENABLE_WARNINGS)
    include(CompilerWarnings)
    set_project_warnings(perf-lab)
endif()

add_subdirectory(src)
# add_subdirectory(apps)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
# =============================================================================
# perf-lab — Low-latency performance playground for embedded C
# https://github.com/AuWwow/perf-lab
# =============================================================================

cmake_minimum_required(VERSION 3.20)   # 3.20+ для лучшей поддержки ARM / RP2040
project(perf-lab LANGUAGES C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ─── Target selection ────────────────────────────────────────────────────────
if(NOT DEFINED TARGET)
    set(TARGET "host" CACHE STRING "Build target: host | pico | renode")
endif()

string(TOLOWER "${TARGET}" TARGET_LOWER)
message(STATUS "Building for target: ${TARGET} (${TARGET_LOWER})")

# ─── Paths & modules ─────────────────────────────────────────────────────────
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# ─── Global warnings + hardening (можно выключить через -D) ──────────────────
option(ENABLE_WARNINGS "Enable strict compiler warnings" ON)
if(ENABLE_WARNINGS)
    include(CompilerWarnings)
    # set_project_warnings будет вызвана позже на конкретных target'ах
endif()

option(ENABLE_SANITIZERS "Enable address/undefined sanitizers (host only)" OFF)

# ─── Common interface library for shared compile options ─────────────────────
add_library(common_flags INTERFACE)
target_compile_options(common_flags INTERFACE
    -Wall -Wextra -Wshadow -Wformat=2 -Wundef -Wconversion
    $<$<CONFIG:Debug>:-Og -g3>
    $<$<CONFIG:Release>:-O2 -DNDEBUG>
)

if(ENABLE_SANITIZERS AND "${TARGET_LOWER}" STREQUAL "host")
    target_compile_options(common_flags INTERFACE -fsanitize=address,undefined)
    target_link_options(common_flags INTERFACE -fsanitize=address,undefined)
endif()

# ─── Subdirectories ──────────────────────────────────────────────────────────
add_subdirectory(src)                   # middleware + app + shared

# Map target to directory
if(TARGET_LOWER STREQUAL "host")
    set(TARGET_DIR "host-sim")
elseif(TARGET_LOWER STREQUAL "pico")
    set(TARGET_DIR "rp2040-pico")
elseif(TARGET_LOWER STREQUAL "renode")
    set(TARGET_DIR "renode-stm32f4")
elseif(TARGET_LOWER STREQUAL "my-rtos")
    set(TARGET_DIR "my-rtos")
else()
    message(FATAL_ERROR "Unknown target: ${TARGET}")
endif()

# Target-specific configuration & executable(s)
add_subdirectory(targets/${TARGET_DIR})

# Tests only for host
option(BUILD_TESTS "Build unit & stress tests" OFF)
if(BUILD_TESTS AND "${TARGET_LOWER}" STREQUAL "host")
    enable_testing()
    add_subdirectory(tests)
endif()

# ─── Final message ───────────────────────────────────────────────────────────
message(STATUS "──────────────────────────────────────────────")
message(STATUS "  Target          : ${TARGET}")
message(STATUS "  Build type      : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Warnings        : ${ENABLE_WARNINGS}")
message(STATUS "  Sanitizers      : ${ENABLE_SANITIZERS}")
message(STATUS "──────────────────────────────────────────────")
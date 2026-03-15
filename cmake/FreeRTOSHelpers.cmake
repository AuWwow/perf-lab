# FreeRTOSHelpers.cmake - Helper functions for FreeRTOS integration

# Add FreeRTOS kernel library
if(NOT TARGET freertos_kernel)
    # Assume FreeRTOS is in external/FreeRTOS-Kernel
    set(FREERTOS_DIR "${CMAKE_SOURCE_DIR}/external/FreeRTOS-Kernel")

    if(NOT EXISTS "${FREERTOS_DIR}")
        message(FATAL_ERROR "FreeRTOS-Kernel not found in ${FREERTOS_DIR}. Please initialize submodules.")
    endif()

    # Add FreeRTOS sources
    file(GLOB FREERTOS_SOURCES
        "${FREERTOS_DIR}/list.c"
        "${FREERTOS_DIR}/queue.c"
        "${FREERTOS_DIR}/tasks.c"
        "${FREERTOS_DIR}/timers.c"
        "${FREERTOS_DIR}/portable/${FREERTOS_PORT}/*.c"
        "${FREERTOS_DIR}/portable/MemMang/heap_4.c"
    )

    add_library(freertos_kernel STATIC ${FREERTOS_SOURCES})

    target_include_directories(freertos_kernel PUBLIC
        "${FREERTOS_DIR}/include"
        "${FREERTOS_DIR}/portable/${FREERTOS_PORT}"
    )
endif()

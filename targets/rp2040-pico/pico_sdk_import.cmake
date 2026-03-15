# pico_sdk_import.cmake - Import Pico SDK

# This file should be provided by the pico-sdk submodule
# For now, this is a placeholder

if(NOT PICO_SDK_PATH)
    set(PICO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/pico-sdk")
endif()

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
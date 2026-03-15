# Sanitizers.cmake - Sanitizer configuration

option(ENABLE_SANITIZERS "Enable sanitizers for debugging" OFF)

if(ENABLE_SANITIZERS)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-fsanitize=address -fsanitize=undefined)
        add_link_options(-fsanitize=address -fsanitize=undefined)
    endif()
endif()
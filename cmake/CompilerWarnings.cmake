# CompilerWarnings.cmake - Compiler warning flags

function(set_project_warnings target)
    if(ENABLE_WARNINGS)
        if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(${target} PRIVATE
                -Wall -Wextra -Wshadow -Wformat=2 -Wundef -Wconversion
            )
        endif()
    endif()
endfunction()

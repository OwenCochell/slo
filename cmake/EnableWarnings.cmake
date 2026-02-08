#=============================================================================
# Helper function to enable all warnings for a target
# This is done in a compiler independent way.
#
# Usage: enable_warnings(<target>)

function(enable_warnings target)
    if(MSVC)
        # We are a microsoft compiler, need special flags
        target_compile_options(${target} INTERFACE /W4)
    else()
        # We are likely a compiler on a POSIX system,
        # which means it likely knows these warning arguments
        target_compile_options(${target} INTERFACE -Wall -Wextra -Wpedantic)
    endif()
endfunction(enable_warnings target)

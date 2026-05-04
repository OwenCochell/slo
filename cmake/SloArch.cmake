#=============================================================================
# Helper function to link an architecture to a target.
# This will handle all of the necessary setup that some arches require.
# Once complete, your target will have access to all arch-specific features and libraries.
#
# Usage: slo_target_arch(<target>)

function(slo_target_arch target)
  if(NOT TARGET arch)
    message(FATAL_ERROR "slo_target_arch(${target}): no 'arch' target — root CMakeLists didn't add_subdirectory(arch/<SLO_ARCH>)?")
  endif()
  target_link_libraries(${target} PUBLIC arch)
endfunction()

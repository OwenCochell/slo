cmake_minimum_required(VERSION 3.25)

###
# Option Definitions
###

set(SLO_ARCH "arduino" CACHE STRING "Target architecture to build for")

# Add cmake modules to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include some CMake functions we use globally
include(EnableWarnings)
include(SloArch)

# Determine if CMAKE_BUILD_TYPE is not defied

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")

  # Set the build type to Release

  set(CMAKE_BUILD_TYPE "Release")
endif()

# We need invoke any arch setup files

set(_slo_arch_dir "${CMAKE_CURRENT_SOURCE_DIR}/arch/${SLO_ARCH}")
set(_slo_arch_setup "${_slo_arch_dir}/setup.cmake")
if(NOT EXISTS "${_slo_arch_setup}")
  message(FATAL_ERROR "No arch/${SLO_ARCH}/setup.cmake — invalid SLO_ARCH")
endif()
include("${_slo_arch_setup}")

project(slo VERSION 0.0.1 DESCRIPTION "Snail Logistics Orchestrator" LANGUAGES CXX C)

# Add the arch directory
add_subdirectory(${_slo_arch_dir})
# Pull in global external dependencies
add_subdirectory(extern)
# Pull in all libraries in use
add_subdirectory(libs)

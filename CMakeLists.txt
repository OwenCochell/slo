cmake_minimum_required(VERSION 3.25)

project(slo VERSION 0.0.1 DESCRIPTION "Snail Logistics Orchestrator" LANGUAGES CXX)

# Add cmake modules to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include some CMake functions we use globally
include(EnableWarnings)

# Determine if CMAKE_BUILD_TYPE is not defied

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")

  # Set the build type to Release

  set(CMAKE_BUILD_TYPE "Release")
endif()

# Pull in global external dependencies
add_subdirectory(extern)
# We need to pull in arch components for libraries
add_subdirectory(arch)
# Pull in all libraries in use
add_subdirectory(libs)

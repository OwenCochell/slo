cmake_minimum_required(VERSION 3.25)

project(slo VERSION 0.0.1 DESCRIPTION "Snail Logistics Orchestrator" LANGUAGES CXX)

# Add cmake modules to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Determine if CMAKE_BUILD_TYPE is not defied

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")

  # Set the build type to Release

  set(CMAKE_BUILD_TYPE "Release")
endif()

# Add the various libraries in this project

add_subdirectory(arch)
add_subdirectory(libs)

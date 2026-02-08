#=============================================================================
# SLO Standard Library - snalib

cmake_minimum_required(VERSION 3.25)

set(CMAKE_FOLDER libs/snalib)

add_library(snalib STATIC
    src/memory.cpp
)

target_include_directories(snalib
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(snalib PUBLIC arch)

target_compile_features(snalib PUBLIC cxx_std_20)

enable_warnings(snalib)

# Add tests for snalib

add_subdirectory(test)

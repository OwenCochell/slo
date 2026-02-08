#=============================================================================
# SLO Standard Library - snalib

cmake_minimum_required(VERSION 3.25)

add_library(snalib STATIC
    src/memory.cpp
)

target_include_directories(snalib
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(snalib arch)

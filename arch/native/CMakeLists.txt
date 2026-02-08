#=============================================================================
# Native architecture, allows SLO to run on a architecture
# native to the system we compiling on

cmake_minimum_required(VERSION 3.25)

add_library(native_arch STATIC
    src/memory.cpp
)

target_include_directories(native_arch
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(arch ALIAS native_arch)

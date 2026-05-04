#=============================================================================
# Arduino Architecture, allows SLO to run on arduino boards

# Set the toolchain to be the arduino toolchain,
# this should be project wide

cmake_minimum_required(VERSION 3.25)

# Add the cmake modules for this arch

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# We need the arduino target to link against
if(NOT TARGET ArduinoCore::Core)
  include(ArduinoCore)
endif()

add_library(arduino_arch STATIC
    src/junk.cpp
)

target_include_directories(arduino_arch
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(arduino_arch PUBLIC tenio ArduinoCore::Core)

add_library(arch ALIAS arduino_arch)

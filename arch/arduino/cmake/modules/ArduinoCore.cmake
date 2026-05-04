# ArduinoCore — builds the Arduino runtime ("core") into a static library.
#
# Targets:
#   ArduinoCore::Headers — INTERFACE, exposes core+variant include dirs
#   ArduinoCore::Core    — STATIC library of the core+variant sources

include_guard(GLOBAL)

if(TARGET ArduinoCore::Core)
  return()
endif()

if(NOT ARDUINO_CORE_PATH OR NOT ARDUINO_VARIANT_PATH)
  message(FATAL_ERROR "ArduinoCore.cmake: load arduino-toolchain.cmake first (ARDUINO_CORE_PATH unset)")
endif()

add_library(ArduinoCoreHeaders INTERFACE)
# Use -I (not -isystem): avr-gcc has a long-standing quirk where SYSTEM
# include dirs implicitly extend extern "C" linkage into Arduino.h, breaking
# C++ overload declarations (makeWord, random, operator+).
target_include_directories(ArduinoCoreHeaders INTERFACE
  "${ARDUINO_CORE_PATH}"
  "${ARDUINO_VARIANT_PATH}"
)
add_library(ArduinoCore::Headers ALIAS ArduinoCoreHeaders)

file(GLOB_RECURSE _core_c   CONFIGURE_DEPENDS "${ARDUINO_CORE_PATH}/*.c")
file(GLOB_RECURSE _core_cxx CONFIGURE_DEPENDS "${ARDUINO_CORE_PATH}/*.cpp")
file(GLOB_RECURSE _core_asm CONFIGURE_DEPENDS "${ARDUINO_CORE_PATH}/*.S")

# The host project may only have enabled CXX. The Arduino core needs C and
# possibly ASM, so opportunistically turn them on.
if(_core_c)
  enable_language(C)
endif()
if(_core_asm)
  enable_language(ASM)
endif()

add_library(ArduinoCoreLib STATIC ${_core_c} ${_core_cxx} ${_core_asm})
target_link_libraries(ArduinoCoreLib PUBLIC ArduinoCoreHeaders)
set_target_properties(ArduinoCoreLib PROPERTIES OUTPUT_NAME core)
add_library(ArduinoCore::Core ALIAS ArduinoCoreLib)

# Pre-project setup for the Arduino arch.
# This file is included from the root CMakeLists.txt BEFORE project().

option(ARDUINO_USE_SYSTEM_TOOLCHAIN "Use system toolchain file instead of the one provided by this project" ON)

set(CMAKE_TOOLCHAIN_FILE
    "${CMAKE_CURRENT_LIST_DIR}/cmake/arduino-toolchain.cmake"
    CACHE FILEPATH "Arduino toolchain" FORCE)

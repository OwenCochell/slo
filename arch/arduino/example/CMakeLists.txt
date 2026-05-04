# Standalone test of the arduino-cli toolchain.
# Build with:
#   cmake -S . -B build \
#         -DCMAKE_TOOLCHAIN_FILE=../cmake/arduino-toolchain.cmake \
#         -DARDUINO_FQBN=arduino:avr:uno
#   cmake --build build

cmake_minimum_required(VERSION 3.25)
project(arduino_example LANGUAGES C CXX)

include(ArduinoHelpers)

arduino_executable(blink SOURCES blink.cpp)
arduino_upload(blink)

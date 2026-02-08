project(snalib-test)

set(TEST_FILES
    array.cpp
)

# Enable testing for this project
enable_testing()

# Define the executable target name

set(TEST_NAME snalib_test)

# Add the tests target
add_executable(${TEST_NAME} ${TEST_FILES})

# Make Catch2 available to this file
FetchContent_MakeAvailable(Catch2)

# Linking test with the Catch2 and aglink libraries
target_link_libraries(${TEST_NAME} PRIVATE snalib Catch2::Catch2WithMain)

# Define C++ standard:
target_compile_features(${TEST_NAME} INTERFACE cxx_std_20)

# Add Catch2 extra modules to the CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# Include Catch2 CMake files
include(Catch)

# Discover and register all tests
catch_discover_tests(${TEST_NAME})

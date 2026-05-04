#=============================================================================
# Tentacle IO GPIO Abstraction Library - tenio

cmake_minimum_required(VERSION 3.25)

set(CMAKE_FOLDER libs/tenio)

add_library(tenio STATIC
    src/junk.cpp
)

target_include_directories(tenio
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(tenio PUBLIC snalib)

target_compile_features(tenio PUBLIC cxx_std_20)

enable_warnings(tenio)

# Add tests for tenio

#add_subdirectory(test)

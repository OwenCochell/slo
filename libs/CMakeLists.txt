
# Group all files under a group
set(CMAKE_FOLDER libs)

# Add snalib, the SLO standard library
add_subdirectory(snalib)

# Add Tentacle IO, the GPIO abstraction library
add_subdirectory(tentacle)

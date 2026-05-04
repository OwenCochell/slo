# Group targets under one group

set(CMAKE_FOLDER extern)

# We only want catch2 if we are native
if(NOT CMAKE_CROSSCOMPILING)
    add_subdirectory(catch2)
endif()

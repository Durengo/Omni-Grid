find_package(GTest CONFIG REQUIRED)

add_subdirectory("Framework")
add_subdirectory("Games")

if(${VERBOSE})
    message(STATUS "OMNI-GRID GTEST SUITE ADDED.")
endif()
find_package(GTest CONFIG REQUIRED)

add_subdirectory("framework")

if(${VERBOSE})
    message(STATUS "OMNI-GRID GTEST SUITE ADDED.")
endif()
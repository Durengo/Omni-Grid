# PYTHON LIBRARY.
add_library(HelloBoostPythonLib SHARED "HelloBoostPythonLib.cpp")

message(STATUS "PYTHON3_LIBRARIES: ${Boost_LIBRARIES}")

target_link_libraries(HelloBoostPythonLib PRIVATE
    ${Python3_LIBRARIES}
    ${Boost_LIBRARIES}
    ${VCPKG_CORE}/lib/${PYTHON_VERSION}.lib
)

target_include_directories(HelloBoostPythonLib PRIVATE
    ${Python3_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

set_target_properties(HelloBoostPythonLib PROPERTIES SUFFIX ".pyd")
set(CMAKE_SHARED_MODULE_PREFIX "")

Install(TARGETS HelloBoostPythonLib
    LIBRARY DESTINATION examples/python
    ARCHIVE DESTINATION examples/python
    RUNTIME DESTINATION examples/python)

install(FILES $<TARGET_RUNTIME_DLLS:HelloBoostPythonLib> DESTINATION examples/python)

# PYTHON EXECUTABLE.
add_executable(OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE "HelloBoostPythonExe.cpp")

target_link_libraries(OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE PRIVATE
    ${Python3_LIBRARIES}
    ${Boost_LIBRARIES}
    ${VCPKG_CORE}/lib/${PYTHON_VERSION}.lib
)
target_include_directories(OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE PRIVATE
    ${Python3_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

set_target_properties(OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE PROPERTIES OUTPUT_NAME "HelloBoostPythonE")

Install(TARGETS OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE
    LIBRARY DESTINATION examples/python
    ARCHIVE DESTINATION examples/python
    RUNTIME DESTINATION examples/python)

install(FILES $<TARGET_RUNTIME_DLLS:OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE> DESTINATION examples/python)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    install(FILES ${BOOST_PYTHON_DLL_DEBUG_FILES} DESTINATION examples/python)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(FILES ${BOOST_PYTHON_DLL_RELEASE_FILES} DESTINATION examples/python)
endif()

# PYTHON LIBRARIES EXECUTABLE.
add_executable(OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonLibraries "HelloPythonLibraries.cpp")

target_link_libraries(OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonLibraries PRIVATE
    ${Python3_LIBRARIES}
    ${Boost_LIBRARIES}
    ${VCPKG_CORE}/lib/${PYTHON_VERSION}.lib
)
target_include_directories(OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonLibraries PRIVATE
    ${Python3_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

set_target_properties(OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonLibraries PROPERTIES OUTPUT_NAME "BoostPythonLibraries")

Install(TARGETS OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonLibraries
    LIBRARY DESTINATION examples/python
    ARCHIVE DESTINATION examples/python
    RUNTIME DESTINATION examples/python)

install(FILES $<TARGET_RUNTIME_DLLS:OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonLibraries> DESTINATION examples/python)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    install(FILES ${BOOST_PYTHON_DLL_DEBUG_FILES} DESTINATION examples/python)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(FILES ${BOOST_PYTHON_DLL_RELEASE_FILES} DESTINATION examples/python)
endif()

if(${VERBOSE})
    message(STATUS "BOOST PYTHON EXAMPLES ADDED.")
endif()
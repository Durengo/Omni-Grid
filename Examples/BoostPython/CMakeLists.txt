# PYTHON LIBRARY.
add_library(HelloBoostPythonLib SHARED "HelloBoostPythonLib.cpp")

message(STATUS "PYTHON3_LIBRARIES: ${Boost_LIBRARIES}")

target_link_libraries(HelloBoostPythonLib PRIVATE
    ${Python3_LIBRARIES}
    ${Boost_LIBRARIES}
    ${PYTHON_LIB_PATH}
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
    ${PYTHON_LIB_PATH}
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

if(${INSTALL_DLLS})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        install(FILES ${BOOST_PYTHON_DLL_DEBUG_FILES} DESTINATION examples/python)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        install(FILES ${BOOST_PYTHON_DLL_RELEASE_FILES} DESTINATION examples/python)
    endif()
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_custom_command(TARGET OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE POST_BUILD

        # COPY PYTHON RUNTIME DLLS
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Python3_RUNTIME_LIBRARY}"
        $<TARGET_FILE_DIR:OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE>

        # COPY BOOST PYTHON DEBUG DLLS
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Boost_Python_Debug_DLL}"
        $<TARGET_FILE_DIR:OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE>

        # ALSO COPY BOOST PYTHON RELEASE DLLS AS THEY ARE NEEDED FOR RUNTIME
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Boost_Python_Release_DLL}"
        $<TARGET_FILE_DIR:OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE>

        # ALSO COPY ZLIB RELEASE DLLS AS THEY ARE NEEDED FOR RUNTIME
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${VCPKG_CORE}/bin/zlib1.dll"
        $<TARGET_FILE_DIR:OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE>
    )
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_custom_command(TARGET OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE POST_BUILD

        # COPY PYTHON RUNTIME DLLS
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Python3_RUNTIME_LIBRARY}"
        $<TARGET_FILE_DIR:OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE>

        # COPY BOOST PYTHON RELEASE DLLS
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Boost_Python_Release_DLL}"
        $<TARGET_FILE_DIR:OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE>

        # COPY ZLIB RELEASE DLLS
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${VCPKG_CORE}/bin/zlib1.dll"
        $<TARGET_FILE_DIR:OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonEXE>
    )
endif()

# PYTHON LIBRARIES EXECUTABLE.
add_executable(OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonLibraries "HelloPythonLibraries.cpp")

target_link_libraries(OMNI-GRID_EXAMPLES_BOOSTPYTHONHelloBoostPythonLibraries PRIVATE
    ${Python3_LIBRARIES}
    ${Boost_LIBRARIES}
    ${PYTHON_LIB_PATH}
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

if(${INSTALL_DLLS})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        install(FILES ${BOOST_PYTHON_DLL_DEBUG_FILES} DESTINATION examples/python)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        install(FILES ${BOOST_PYTHON_DLL_RELEASE_FILES} DESTINATION examples/python)
    endif()
endif()

if(${VERBOSE})
    message(STATUS "BOOST PYTHON EXAMPLES ADDED.")
endif()
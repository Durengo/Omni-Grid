cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 23)
set(CXX_VERSION_NAME "cxx_std_${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TOGGLE TESTING.
set(MAIN_TEST ON)

# TOGGLE EXAMPLES.
set(EXAMPLES OFF)

# TOGGLE .DLL IN INSTALLS
set(INSTALL_DLLS ON)

# SETTING PROJECT VERSION.
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)
set(PROJECT_VERSION_SUFFIX "a")
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})
set(PROJECT_FULL_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}.${PROJECT_VERSION_SUFFIX})

# CREATING PROJECT.
project(OMNI-GRID-FRAMEWORK VERSION ${PROJECT_VERSION})

# RUN BUILD.PY TO ASSIGN BUILD TYPE.
execute_process(
        COMMAND python "${PROJECT_SOURCE_DIR}/Tools/CPM/PyScripts/build.py" "-cag" "build_type"
        OUTPUT_VARIABLE BUILD_TYPE_SETUP_OUTPUT
        RESULT_VARIABLE BUILD_TYPE_SETUP_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(CMAKE_BUILD_TYPE ${BUILD_TYPE_SETUP_OUTPUT})

# SET INSTALLATION PATH BASED ON BUILD TYPE.
# SETTING BUILD TYPE.
# TOGGLING CUSTOM VERBOSITY.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(INSTALL_PATH_SUFFIX "Debug")
        set(CMAKE_BUILD_TYPE Debug)
        set(VERBOSE ON CACHE INTERNAL "Verbosity on")
        set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(INSTALL_PATH_SUFFIX "Release")
        set(CMAKE_BUILD_TYPE Release)
        set(VERBOSE OFF CACHE INTERNAL "Verbosity off")
        set(CMAKE_EXPORT_COMPILE_COMMANDS FALSE)
else()
        set(INSTALL_PATH_SUFFIX "Unknown")
        set(VERBOSE ON CACHE INTERNAL "Verbosity on")
        message(FATAL_ERROR "UNKNOWN BUILD TYPE: \"${CMAKE_BUILD_TYPE}\".")
endif()

# PATH TO INSTALLATION DIRECTORY.
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/Install/${CMAKE_BUILD_TYPE}" CACHE PATH "Installation Directory" FORCE)

if(${VERBOSE})
        message(STATUS "INSTALLATION SETUP PROCESS STARTING...")
        message(STATUS "DEFAULT INSTALLATION DIRECTORY: \"${CMAKE_INSTALL_PREFIX}\".")
endif()

# CHECKING PLATFORM.
set(CURRENT_PLATFORM "${CMAKE_SYSTEM_NAME}")

if(${VERBOSE})
        message(STATUS "CURRENT PLATFORM: ${CMAKE_SYSTEM_NAME}")
endif()

# DOUBLE CHECKS IF THE SYSTEM IS RUNNING ON X64 SYSTEM.
# THIS ALSO FAILS IF THE COMPILER IS NOT 64-BIT COMPATIBLE.
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
        message(FATAL_ERROR "OMNI-GRID-FRAMEWORK SUPPORTS X64 SYSTEMS ONLY.")
        return()
endif()

# SETTING UP COMPILER.
if(${VERBOSE})
        message(STATUS "SETTING UP COMPILER...")
endif()

string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" LOWER_COMPILER_ID)

if(LOWER_COMPILER_ID STREQUAL "msvc")
        set(CURRENT_COMPILER "MSVC")
        set(COMPILATION_PLATFORM "WIN32")
elseif(LOWER_COMPILER_ID STREQUAL "gnu")
        set(CURRENT_COMPILER "GNU")
        set(COMPILATION_PLATFORM "UNIX")
        message(FATAL_ERROR "GNU COMPILER NOT SUPPORTED.")
elseif(LOWER_COMPILER_ID STREQUAL "clang")
        set(CURRENT_COMPILER "CLANG")
        set(COMPILATION_PLATFORM "UNIX")
        message(FATAL_ERROR "CLANG COMPILER NOT SUPPORTED.")
else()
        message(FATAL_ERROR "COMPILER NOT SUPPORTED.")
endif()

if(${VERBOSE})
        message(STATUS "CURRENT COMPILER PATH: ${CMAKE_CXX_COMPILER}")
        message(STATUS "CURRENT COMPILER: ${CMAKE_CXX_COMPILER_ID}")
        message(STATUS "CURRENT COMPILER VERSION: ${CMAKE_CXX_COMPILER_VERSION}")
        message(STATUS "COMPILER SETUP COMPLETE.")
endif()

# DEPENDENCY MANAGEMENT.
if(COMPILATION_PLATFORM STREQUAL "WIN32")
        set(USE_VCPKG ON)

        if(${VERBOSE})
                message(STATUS "VCPKG STATUS: ${USE_VCPKG}")
        endif()

        # RUN BUILD.PY TO GET VCPKG ROOT PATH.
        execute_process(
                COMMAND python "${PROJECT_SOURCE_DIR}/Tools/CPM/PyScripts/build.py" "-cag" "vcpkg_root"
                OUTPUT_VARIABLE VCPKG_SETUP_OUTPUT
                RESULT_VARIABLE VCPKG_SETUP_RESULT
                OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        set(VCPKG_FILEPATH "${VCPKG_SETUP_OUTPUT}")
        file(TO_CMAKE_PATH "${VCPKG_FILEPATH}/installed/x64-windows" VCPKG_CORE)

        if(NOT EXISTS "${VCPKG_FILEPATH}")
                message(FATAL_ERROR "VCPKG NOT FOUND - MAKE SURE \"${VCPKG_FILEPATH}\" IS SET CORRECTLY.\nCURRENT PATH IS SET TO: \"${VCPKG_FILEPATH}\".")
        endif()

        if(USE_VCPKG)
                if(${VERBOSE})
                        message(STATUS "LOOKING FOR VCPKG IN \"${VCPKG_FILEPATH}\" TO MANAGE DEPENDENCIES.")
                endif()

                # set(X_VCPKG_APPLOCAL_DEPS_INSTALL ON)
                set(CMAKE_TOOLCHAIN_FILE "${VCPKG_FILEPATH}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
                set(CMAKE_PREFIX_PATH "${VCPKG_FILEPATH}/installed/x64-windows")

                if(${VERBOSE})
                        message(STATUS "VCPKG FOUND IN \"${VCPKG_FILEPATH}\".")
                endif()
        endif()
elseif(COMPILATION_PLATFORM STREQUAL "UNIX")
        set(USE_VCPKG OFF)

        if(${VERBOSE})
                message(STATUS "VCPKG STATUS: ${USE_VCPKG}")
        endif()

        message(FATAL_ERROR "VCPKG NOT SUPPORTED ON UNIX SYSTEMS.")
endif()

# ADDING DEPENDENCIES.
if(${VERBOSE})
        message(STATUS "LOOKING FOR DEPENDENCIES...")
endif()

find_package(Git QUIET)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

if(${VERBOSE})
        message(STATUS "LOOKING FOR DURLIB...")
endif()

set(DURLIB_DIRECTORY "${PROJECT_SOURCE_DIR}/Library/durlib")

if(EXISTS ${DURLIB_DIRECTORY})
        message(STATUS "THE DIRECTORY \'${DURLIB_DIRECTORY}\' FOUND.")
else()
        message(FATAL_ERROR "THE DIRECTORY \'${DURLIB_DIRECTORY}\' NOT FOUND.\nPLEASE RUN \"git submodule update --init --recursive\" TO GET THE DEPENDENCIES.")
endif()

configure_file(
        "${PROJECT_SOURCE_DIR}/Tools/CPM/Cache/options_cache.json"
        "${PROJECT_SOURCE_DIR}/Library/durlib/scripts/options_cache.json"
        COPYONLY
)

add_subdirectory(${DURLIB_DIRECTORY})

if(${VERBOSE})
        message(STATUS "DURLIB FOUND.")
endif()

if(${VERBOSE})
        message(STATUS "ALL DEPENDENCIES FOUND.")
endif()

# ADDING TESTING ENVIRONMENT.
if(${VERBOSE})
        message(STATUS "ADDING TESTING ENVIRONMENT...")
endif()

include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_FULL_VERSION})
include(CPack)

if(${VERBOSE})
        message(STATUS "TESTING ENVIRONMENT ADDED.")
endif()

# ADDITIONAL INFORMATION.
if(${VERBOSE})
        message(STATUS "CURRENT BUILD TYPE: ${CMAKE_BUILD_TYPE}")
        message(STATUS "PROJECT VERSION: \"${PROJECT_FULL_VERSION}\".")
        message(STATUS "TOOLCHAIN STATUS: \"${CMAKE_TOOLCHAIN_FILE}\".")
        message(STATUS "CMAKE INCLUDE CURRENT DIRECTORY: \"${CMAKE_INCLUDE_CURRENT_DIR}\".")
        message(STATUS "CTEST STATUS: \"${CPACK_PROJECT_NAME}\" VERSION \"${CPACK_PROJECT_VERSION}\".")
endif()

# CHECK IF SYSTEMS IS RUNNING WINDOWS AND ADD NECESSARY ATTRIBUTES.
# EVEN THOUGH CURRENTLY ONLY WINDOWS IS SUPPORTED, ADDING THIS CHECK WILL MAKE IT EASIER TO ADD SUPPORT FOR OTHER SYSTEMS IN THE FUTURE.
if(COMPILATION_PLATFORM STREQUAL "WIN32")
        # INSTALLATION FOR LIBRARIES.

        # RAYLIB DEBUG DLLS.
        set(RAYLIB_DLL_DEBUG_FILES
                ${VCPKG_CORE}/debug/bin/raylib.dll
        )

        # RAYLIB RELEASE DLLS.
        set(RAYLIB_DLL_RELEASE_FILES
                ${VCPKG_CORE}/bin/raylib.dll
        )

        # ADD SOURCE FILES
        # OMNI-GRID .CPP FILES
        file(GLOB_RECURSE OMNI-GRID_CPP

                # CORE
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Player/*.cpp"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Grid/*.cpp"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/GameLogicInterface/*.cpp"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/GameLogicImplementation/*.cpp"

                # GUI
                "${PROJECT_SOURCE_DIR}/Source/ogrid/GUI/*.cpp"

                # GAMES
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Games/TicTacToe/*.cpp"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Games/ConnectFour/*.cpp"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Games/Checkers/*.cpp"

                # USER
                "${PROJECT_SOURCE_DIR}/Source/ogrid/User/*.cpp"

                # TOOLS
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Tools/Database/*.cpp"
        )

        # OMNI-GRID .H FILES
        file(GLOB_RECURSE OMNI-GRID_H

                # IMPORT HEADERS
                "${PROJECT_SOURCE_DIR}/Source/ogrid/ogrid.h"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/ogrid_gui.h"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/ogrid_fmt.h"

                # CORE
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Player/*.h"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Grid/*.h"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/GameLogicInterface/*.h"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/GameLogicImplementation/*.h"

                # GUI
                "${PROJECT_SOURCE_DIR}/Source/ogrid/GUI/*.h"

                # GAMES
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Games/TicTacToe/*.h"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Games/ConnectFour/*.h"
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Games/Checkers/*.h"

                # USER
                "${PROJECT_SOURCE_DIR}/Source/ogrid/User/*.h"

                # TOOLS
                "${PROJECT_SOURCE_DIR}/Source/ogrid/Tools/Database/*.h"
        )

        if(${VERBOSE})
                message(STATUS "OMNI-GRID SOURCE FILES ADDED.")
        endif()

        add_library(OMNI-GRID STATIC ${OMNI-GRID_CPP})

        # add_executable(OMNI-GRID ${OMNI-GRID_CPP} ${OMNI-GRID_H})
        target_compile_features(OMNI-GRID PUBLIC ${CXX_VERSION_NAME})
        set_target_properties(OMNI-GRID PROPERTIES VERSION ${PROJECT_FULL_VERSION})

        set_target_properties(OMNI-GRID PROPERTIES OUTPUT_NAME "OMNI-GRID")

        target_link_libraries(OMNI-GRID PUBLIC
                DURLIB
                fmt::fmt
                spdlog::spdlog
                OpenGL::GL
                ${OPENGL_LIBRARIES}
                ${raylib_LIBRARIES}
                unofficial::sqlite3::sqlite3
        )

        target_precompile_headers(OMNI-GRID PUBLIC
                "${PROJECT_SOURCE_DIR}/Source/ogrid/PCH.h"
        )

        target_include_directories(OMNI-GRID PUBLIC
                ${OMNI-GRID_H}
                "${PROJECT_SOURCE_DIR}/Source/ogrid"
                ${OPENGL_INCLUDE_DIR}
                ${raylib_INCLUDE_DIRS}
        )

        # COMPILER DEFINITIONS FOR OMNI-GRID.
        target_compile_definitions(OMNI-GRID PUBLIC OGRID_PLATFORM_WINDOWS)
        target_compile_definitions(OMNI-GRID PUBLIC OGRID_STATIC_LIBRARY)
        target_compile_definitions(OMNI-GRID PUBLIC OGRID_ENABLE_ASSERTS)
        target_compile_definitions(OMNI-GRID PUBLIC OGRID_COMPILER_${CURRENT_COMPILER})

        # ENABLE PROFILING FOR DEBUG BUILDS.
        if(CMAKE_BUILD_TYPE STREQUAL Debug)
                target_compile_definitions(OMNI-GRID PUBLIC OGRID_DEBUG_PROFILING)
                target_compile_definitions(OMNI-GRID PUBLIC OGRID_ENABLE_DEBUG_LOG)
        endif(CMAKE_BUILD_TYPE STREQUAL Debug)

        if(${VERBOSE})
                get_target_property(DEFINITIONS_LIST OMNI-GRID COMPILE_DEFINITIONS)
                message(STATUS "OMNI-GRID COMPILE DEFINITIONS: ${DEFINITIONS_LIST}")
        endif()

        if(${MAIN_TEST})
                add_subdirectory("${PROJECT_SOURCE_DIR}/Tests")
        endif()

        if(${EXAMPLES})
                add_subdirectory("${PROJECT_SOURCE_DIR}/Examples")
        endif()

        # INSTALLATION PROCEDURE.
        install(TARGETS OMNI-GRID
                LIBRARY DESTINATION bin
                ARCHIVE DESTINATION bin
                RUNTIME DESTINATION bin)

        if(${INSTALL_DLLS})
                if(CMAKE_BUILD_TYPE STREQUAL "Debug")
                        # install(FILES ${GTK_DLL_DEBUG_FILES} DESTINATION bin)
                        install(FILES ${RAYLIB_DLL_DEBUG_FILES} DESTINATION bin)

                # install(FILES ${BOOST_PYTHON_DLL_DEBUG_FILES} DESTINATION bin)
                elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
                        # install(FILES ${GTK_DLL_RELEASE_FILES} DESTINATION bin)
                        install(FILES ${RAYLIB_DLL_RELEASE_FILES} DESTINATION bin)

                        # install(FILES ${BOOST_PYTHON_DLL_RELEASE_FILES} DESTINATION bin)
                endif()
        endif()

        # TODO: Find a way to fix this issue without having to run a script or manually copying the dlls.
        # install(SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/utils/core_copy_missing_dlls.cmake")

        # ADD SOURCE FILES
        # Ogrid-Sandbox .CPP FILES
        file(GLOB_RECURSE Ogrid-Sandbox_CPP
                "${PROJECT_SOURCE_DIR}/Source/Sandbox/Core/*.cpp"
                "${PROJECT_SOURCE_DIR}/Source/Sandbox/GUI/*.cpp"
        )

        # Ogrid-Sandbox .H FILES
        file(GLOB_RECURSE Ogrid-Sandbox_H
                "${PROJECT_SOURCE_DIR}/Source/Sandbox/Core/*.h"
                "${PROJECT_SOURCE_DIR}/Source/Sandbox/GUI/*.h"
        )

        if(${VERBOSE})
                message(STATUS "Ogrid-Sandbox SOURCE FILES ADDED.")
        endif()

        add_executable(Ogrid-Sandbox
                "${PROJECT_SOURCE_DIR}/Source/Sandbox/main.cpp"
                ${Ogrid-Sandbox_CPP}
                ${Ogrid-Sandbox_H}
        )

        target_compile_features(Ogrid-Sandbox PUBLIC ${CXX_VERSION_NAME})
        set_target_properties(Ogrid-Sandbox PROPERTIES VERSION ${PROJECT_FULL_VERSION})

        set_target_properties(Ogrid-Sandbox PROPERTIES OUTPUT_NAME "Ogrid-Sandbox")
        target_link_libraries(Ogrid-Sandbox PUBLIC
                OMNI-GRID
        )

        target_include_directories(Ogrid-Sandbox PUBLIC
                "${PROJECT_SOURCE_DIR}/Source/Sandbox"
                ${Ogrid-Sandbox_H}
        )

        # COMPILER DEFINITIONS FOR Ogrid-Sandbox.
        target_compile_definitions(Ogrid-Sandbox PUBLIC GWS_PLATFORM_WINDOWS)

        target_compile_definitions(Ogrid-Sandbox PUBLIC GWS_ENABLE_ASSERTS)
        target_compile_definitions(Ogrid-Sandbox PUBLIC GWS_COMPILER_${CURRENT_COMPILER})

        # ENABLE PROFILING FOR DEBUG BUILDS.
        if(CMAKE_BUILD_TYPE STREQUAL Debug)
                target_compile_definitions(Ogrid-Sandbox PUBLIC GWS_DEBUG_PROFILING)
                target_compile_definitions(Ogrid-Sandbox PUBLIC GWS_ENABLE_DEBUG_LOG)
        endif(CMAKE_BUILD_TYPE STREQUAL Debug)

        if(${VERBOSE})
                get_target_property(DEFINITIONS_LIST Ogrid-Sandbox COMPILE_DEFINITIONS)
                message(STATUS "Ogrid-Sandbox COMPILE DEFINITIONS: ${DEFINITIONS_LIST}")
        endif()

        # INSTALLATION PROCEDURE.
        install(TARGETS Ogrid-Sandbox
                LIBRARY DESTINATION bin
                ARCHIVE DESTINATION bin
                RUNTIME DESTINATION bin)

        install(FILES $<TARGET_RUNTIME_DLLS:Ogrid-Sandbox> DESTINATION bin)
endif()

message(STATUS "OMNI-GRID/CMAKE SUCCESSFULLY FINISHED.")

set(BUILD_SHARED_LIBS ON)

add_executable(HelloRaylib "HelloRaylib.cpp")

target_link_libraries(HelloRaylib PRIVATE
    raylib
)

set_target_properties(HelloRaylib PROPERTIES OUTPUT_NAME "HelloRaylib")

Install(TARGETS HelloRaylib
    LIBRARY DESTINATION examples/raylib
    ARCHIVE DESTINATION examples/raylib
    RUNTIME DESTINATION examples/raylib)

install(FILES $<TARGET_RUNTIME_DLLS:HelloRaylib> DESTINATION examples/raylib)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    install(FILES ${RAYLIB_DLL_DEBUG_FILES} DESTINATION examples/raylib)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    install(FILES ${RAYLIB_DLL_RELEASE_FILES} DESTINATION examples/raylib)
endif()

if(${VERBOSE})
    message(STATUS "RAYLIB EXAMPLES ADDED.")
endif()
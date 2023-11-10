add_executable(OMNI-GRID_EXAMPLES_HELLOGTK "HelloGtk.cpp")

target_link_libraries(OMNI-GRID_EXAMPLES_HELLOGTK PRIVATE
    PkgConfig::GTKMM_LIB
)

target_include_directories(OMNI-GRID_EXAMPLES_HELLOGTK PRIVATE
    ${GTKMM_LIB_INCLUDE_DIRS}
)

set_target_properties(OMNI-GRID_EXAMPLES_HELLOGTK PROPERTIES OUTPUT_NAME "HelloGtk")

Install(TARGETS OMNI-GRID_EXAMPLES_HELLOGTK
    LIBRARY DESTINATION examples/gtk
    ARCHIVE DESTINATION examples/gtk
    RUNTIME DESTINATION examples/gtk)

install(FILES $<TARGET_RUNTIME_DLLS:OMNI-GRID_EXAMPLES_HELLOGTK> DESTINATION examples/gtk)

if(${INSTALL_DLLS})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        install(FILES ${GTK_DLL_DEBUG_FILES} DESTINATION examples/gtk)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        install(FILES ${GTK_DLL_RELEASE_FILES} DESTINATION examples/gtk)
    endif()
endif()

if(${VERBOSE})
    message(STATUS "GTK EXAMPLES ADDED.")
endif()
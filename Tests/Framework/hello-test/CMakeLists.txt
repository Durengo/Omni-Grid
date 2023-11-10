add_executable(Tests-Framework-HelloFramework "HelloFramework.cpp")

set_target_properties(Tests-Framework-HelloFramework PROPERTIES OUTPUT_NAME "Tests-HelloFramework")
target_link_libraries(Tests-Framework-HelloFramework PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(FrameworkGTest Tests-Framework-HelloFramework)

install(TARGETS Tests-Framework-HelloFramework
    RUNTIME DESTINATION tests/framework
    LIBRARY DESTINATION tests/framework
    ARCHIVE DESTINATION tests/framework)
install(FILES $<TARGET_RUNTIME_DLLS:Tests-Framework-HelloFramework> DESTINATION tests/framework)

if(${VERBOSE})
    message(STATUS "FRAMEWORK HELLO TEST ADDED.")
endif()
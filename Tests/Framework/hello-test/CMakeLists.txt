add_executable(Test-Framework-HelloFramework "HelloFramework.cpp")

set_target_properties(Test-Framework-HelloFramework PROPERTIES OUTPUT_NAME "Test-Framework-HelloFramework")
target_link_libraries(Test-Framework-HelloFramework PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(FrameworkGTest Test-Framework-HelloFramework)

install(TARGETS Test-Framework-HelloFramework
    RUNTIME DESTINATION tests/framework
    LIBRARY DESTINATION tests/framework
    ARCHIVE DESTINATION tests/framework)
install(FILES $<TARGET_RUNTIME_DLLS:Test-Framework-HelloFramework> DESTINATION tests/framework)

if(${VERBOSE})
    message(STATUS "FRAMEWORK HELLO TEST ADDED.")
endif()
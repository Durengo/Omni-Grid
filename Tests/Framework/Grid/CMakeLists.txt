add_executable(Test-Framework-Grid "GridTest.cpp")

set_target_properties(Test-Framework-Grid PROPERTIES OUTPUT_NAME "Test-Framework-Grid")
target_link_libraries(Test-Framework-Grid PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(FrameworkGTest Test-Framework-Grid)

install(TARGETS Test-Framework-Grid
    RUNTIME DESTINATION tests/framework
    LIBRARY DESTINATION tests/framework
    ARCHIVE DESTINATION tests/framework)
install(FILES $<TARGET_RUNTIME_DLLS:Test-Framework-Grid> DESTINATION tests/framework)

if(${VERBOSE})
    message(STATUS "FRAMEWORK GRID TEST ADDED.")
endif()
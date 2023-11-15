add_executable(Test-Framework-GameLogic "GameLogicTest.cpp")

set_target_properties(Test-Framework-GameLogic PROPERTIES OUTPUT_NAME "Test-Framework-GameLogic")
target_link_libraries(Test-Framework-GameLogic PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(FrameworkGTest Test-Framework-GameLogic)

install(TARGETS Test-Framework-GameLogic
    RUNTIME DESTINATION tests/framework
    LIBRARY DESTINATION tests/framework
    ARCHIVE DESTINATION tests/framework)
install(FILES $<TARGET_RUNTIME_DLLS:Test-Framework-GameLogic> DESTINATION tests/framework)

if(${VERBOSE})
    message(STATUS "FRAMEWORK GAMELOGIC TEST ADDED.")
endif()
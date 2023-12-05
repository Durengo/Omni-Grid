add_executable(Test-Framework-GameConfiguration "GameConfigurationTest.cpp")

set_target_properties(Test-Framework-GameConfiguration PROPERTIES OUTPUT_NAME "Test-Framework-GameConfiguration")
target_link_libraries(Test-Framework-GameConfiguration PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(FrameworkGTestP1 Test-Framework-GameConfiguration)

install(TARGETS Test-Framework-GameConfiguration
    RUNTIME DESTINATION tests/framework
    LIBRARY DESTINATION tests/framework
    ARCHIVE DESTINATION tests/framework)
install(FILES $<TARGET_RUNTIME_DLLS:Test-Framework-GameConfiguration> DESTINATION tests/framework)

if(${VERBOSE})
    message(STATUS "FRAMEWORK GAME CONFIGURATION TEST ADDED.")
endif()

add_executable(Test-Framework-GameStateExtensions "GameStateExtensionsTest.cpp")

set_target_properties(Test-Framework-GameStateExtensions PROPERTIES OUTPUT_NAME "Test-Framework-GameStateExtensions")
target_link_libraries(Test-Framework-GameStateExtensions PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(FrameworkGTestP2 Test-Framework-GameStateExtensions)

install(TARGETS Test-Framework-GameStateExtensions
    RUNTIME DESTINATION tests/framework
    LIBRARY DESTINATION tests/framework
    ARCHIVE DESTINATION tests/framework)
install(FILES $<TARGET_RUNTIME_DLLS:Test-Framework-GameStateExtensions> DESTINATION tests/framework)

if(${VERBOSE})
    message(STATUS "FRAMEWORK GAME CONFIGURATION TEST ADDED.")
endif()

# add_executable(Test-Framework-GameLogic "GameLogicTest.cpp")

# set_target_properties(Test-Framework-GameLogic PROPERTIES OUTPUT_NAME "Test-Framework-GameLogic")
# target_link_libraries(Test-Framework-GameLogic PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

# add_test(FrameworkGTestP1 Test-Framework-GameLogic)

# install(TARGETS Test-Framework-GameLogic
#     RUNTIME DESTINATION tests/framework
#     LIBRARY DESTINATION tests/framework
#     ARCHIVE DESTINATION tests/framework)
# install(FILES $<TARGET_RUNTIME_DLLS:Test-Framework-GameLogic> DESTINATION tests/framework)

# if(${VERBOSE})
#     message(STATUS "FRAMEWORK GAMELOGIC TEST ADDED.")
# endif()
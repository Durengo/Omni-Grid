add_executable(Test-Framework-Player "PlayerTest.cpp")

set_target_properties(Test-Framework-Player PROPERTIES OUTPUT_NAME "Test-Framework-Player")
target_link_libraries(Test-Framework-Player PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(FrameworkGTestP1 Test-Framework-Player)

install(TARGETS Test-Framework-Player
    RUNTIME DESTINATION tests/framework
    LIBRARY DESTINATION tests/framework
    ARCHIVE DESTINATION tests/framework)
install(FILES $<TARGET_RUNTIME_DLLS:Test-Framework-Player> DESTINATION tests/framework)

if(${VERBOSE})
    message(STATUS "FRAMEWORK PLAYER TEST ADDED.")
endif()

add_executable(Test-Framework-Piece "PieceTest.cpp")

set_target_properties(Test-Framework-Piece PROPERTIES OUTPUT_NAME "Test-Framework-Piece")
target_link_libraries(Test-Framework-Piece PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(FrameworkGTestP2 Test-Framework-Piece)

install(TARGETS Test-Framework-Piece
    RUNTIME DESTINATION tests/framework
    LIBRARY DESTINATION tests/framework
    ARCHIVE DESTINATION tests/framework)
install(FILES $<TARGET_RUNTIME_DLLS:Test-Framework-Piece> DESTINATION tests/framework)

if(${VERBOSE})
    message(STATUS "FRAMEWORK PIECE TEST ADDED.")
endif()
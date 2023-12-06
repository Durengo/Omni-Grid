add_executable(Test-Games-TicTacToe "TicTacToeTest.cpp")

set_target_properties(Test-Games-TicTacToe PROPERTIES OUTPUT_NAME "Test-Games-TicTacToe")
target_link_libraries(Test-Games-TicTacToe PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(GamesGTestP1 Test-Games-TicTacToe)

install(TARGETS Test-Games-TicTacToe
    RUNTIME DESTINATION tests/Games
    LIBRARY DESTINATION tests/Games
    ARCHIVE DESTINATION tests/Games)
install(FILES $<TARGET_RUNTIME_DLLS:Test-Games-TicTacToe> DESTINATION tests/Games)
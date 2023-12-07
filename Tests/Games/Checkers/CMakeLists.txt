add_executable(Test-Games-Checkers "CheckersTest.cpp")

set_target_properties(Test-Games-Checkers PROPERTIES OUTPUT_NAME "Test-Games-Checkers")
target_link_libraries(Test-Games-Checkers PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(GamesGTestP1 Test-Games-Checkers)

install(TARGETS Test-Games-Checkers
    RUNTIME DESTINATION tests/Games
    LIBRARY DESTINATION tests/Games
    ARCHIVE DESTINATION tests/Games)
install(FILES $<TARGET_RUNTIME_DLLS:Test-Games-Checkers> DESTINATION tests/Games)
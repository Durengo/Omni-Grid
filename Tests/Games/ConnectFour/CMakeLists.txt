add_executable(Test-Games-ConnectFour "ConnectFourTest.cpp")

set_target_properties(Test-Games-ConnectFour PROPERTIES OUTPUT_NAME "Test-Games-ConnectFour")
target_link_libraries(Test-Games-ConnectFour PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main OMNI-GRID)

add_test(GamesGTestP1 Test-Games-ConnectFour)

install(TARGETS Test-Games-ConnectFour
    RUNTIME DESTINATION tests/Games
    LIBRARY DESTINATION tests/Games
    ARCHIVE DESTINATION tests/Games)
install(FILES $<TARGET_RUNTIME_DLLS:Test-Games-ConnectFour> DESTINATION tests/Games)
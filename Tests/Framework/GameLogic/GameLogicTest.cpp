#include <gtest/gtest.h>

#include <ogrid.h>
#include <durlib.h>

#include <vector>

namespace OGRID
{
    class GameLogicTest : public ::testing::Test
    {
    protected:
        // OGRID::GameLogic *gameLogic;

        Grid *grid;
        unsigned char rowSize = 3;
        unsigned char colSize = 3;
        char initialChar = '.';

        size_t maxPlayers = 2;
        std::vector<Player *> players;

        // void SetUp() override
        // {
        //     OGRID::Game
        //     OGRID::GameLogic::Initialize();
        //     gameLogic = OGRID::GameLogic::GetInstance();

        //     gameLogic->SetGameConfiguration(OGRID::GameConfigurationBuilder()
        //                                         .setGameName("TicTacToe")
        //                                         .setGameDescription("TicTacToe Game")
        //                                         .setGrid(rowSize, colSize, initialChar)
        //                                         .setMaxPlayers(maxPlayers)
        //                                         .addPlayer(new OGRID::Player("Player1", OGRID::PlayerType::Human))
        //                                         .addPlayer(new OGRID::Player("Player2", OGRID::PlayerType::AI))
        //                                         .build());

        //     grid = gameLogic->GetGameConfiguration()->grid;
        //     players.push_back(gameLogic->GetGameConfiguration()->players[0]);
        //     players.push_back(gameLogic->GetGameConfiguration()->players[1]);

        //     gameLogic->SetRandomizeTurnOrder(false);

        //     gameLogic->SetupGame();
        //     gameLogic->StartGame();
        // }

        // void TearDown() override
        // {
        //     gameLogic->DeleteInstance();
        // }
    };

    // // Tests for win conditions
    // TEST_F(GameLogicTest, WinCondition)
    // {
    //     gameLogic->MakeMove(0, 0);
    //     gameLogic->MakeMove(1, 0);
    //     gameLogic->MakeMove(0, 1);
    //     gameLogic->MakeMove(1, 1);
    //     gameLogic->MakeMove(0, 2);

    //     EXPECT_EQ(gameLogic->GetGameState(), GameState::GameOver);
    //     EXPECT_EQ(gameLogic->GetGameOverType(), GameOverType::Win);
    //     EXPECT_EQ(gameLogic->GetWinner(), players[0]);
    // }

    // TEST_F(GameLogicTest, OverwriteMoveAttempt)
    // {
    //     gameLogic->MakeMove(0, 0);                   // Player X makes a move
    //     EXPECT_ANY_THROW(gameLogic->MakeMove(0, 0)); // Player O tries to overwrite X's move
    // }

    TEST_F(GameLogicTest, OverwriteMoveAttempt)
    {
        CLI_TRACE("TEST!");
        // gameLogic->MakeMove(0, 0);                   // Player X makes a move
        // EXPECT_ANY_THROW(gameLogic->MakeMove(0, 0)); // Player O tries to overwrite X's move
    }
}

int main(int argc, char **argv)
{
    DURLIB::Log::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
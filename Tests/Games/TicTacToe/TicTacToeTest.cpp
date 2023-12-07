#include <gtest/gtest.h>

#include <durlib.h>
#include <ogrid.h>

namespace OGRID
{
    class TicTacToeTest : public ::testing::Test
    {
    protected:
        TicTacToe *game;
        GameConfiguration *config;
        Grid *grid;
        Player *playerX;
        Player *playerO;

        void SetUp() override
        {
            playerX = new Player("X", PlayerType::Human, 0);
            playerO = new Player("O", PlayerType::Human, 1);

            game = new TicTacToe();
            game->SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                           .setGameName("TicTacToe")
                                           .setGameDescription("TicTacToe Game")
                                           .setGrid(3, 3)
                                           .setMaxPlayers(2)
                                           .addPlayer(playerX)
                                           .addPlayer(playerO)
                                           .build());

            config = game->GetGameConfiguration();
            grid = config->grid;

            PlayerNameAndPtr playerXNameAndPtr =
                {
                    playerX->GetPlayerName(),
                    playerX};

            PlayerNameAndPtr playerONameAndPtr =
                {
                    playerO->GetPlayerName(),
                    playerO};

            std::vector<PlayerNameAndPtr> playerPairs =
                {
                    playerXNameAndPtr,
                    playerONameAndPtr};

            game->SetPlayerPairs(playerPairs);

            game->SetCurrentPlayer(playerXNameAndPtr);

            game->SetGameStateChecker(new GameStateChecker(new TicTacToeStateCheck()));
        }

        void TearDown() override
        {
            delete game;
            delete config;
            delete grid;
            delete playerX;
            delete playerO;
        }
    };

    TEST_F(TicTacToeTest, TryMakeMove)
    {
        unsigned char row = 0, col = 0;
        // Place 'X' at (0,0)
        EXPECT_TRUE(game->TryMakeMove(row, col));
        EXPECT_EQ(grid->GetPieceAt(0, 0)->GetRepresentation(), "X");

        game->SwitchPlayer();

        row = 1, col = 1;
        // Place 'O' at (1,1)
        EXPECT_TRUE(game->TryMakeMove(row, col));
        EXPECT_EQ(grid->GetPieceAt(1, 1)->GetRepresentation(), "O");

        // Double check the grid
        std::string actual = grid->GetGridAsString();
        std::string expected = "X|NULL|NULL\n"
                               "NULL|O|NULL\n"
                               "NULL|NULL|NULL";

        EXPECT_EQ(actual, expected);
    }

    TEST_F(TicTacToeTest, WinningCondition)
    {
        // Simulate a winning condition
        grid->SetCellAt(0, 0, new XPiece(playerX));
        grid->SetCellAt(0, 1, new XPiece(playerX));
        grid->SetCellAt(0, 2, new XPiece(playerX));

        EXPECT_TRUE(game->IsWinningCondition());
        EXPECT_EQ(game->GetWinner(), playerX);
    }

    TEST_F(TicTacToeTest, LosingCondition)
    {
        // Simulate a losing condition
        grid->SetCellAt(0, 0, new OPiece(playerO));
        grid->SetCellAt(0, 1, new OPiece(playerO));
        grid->SetCellAt(0, 2, new OPiece(playerO));

        EXPECT_TRUE(game->IsWinningCondition());
        EXPECT_NE(game->GetWinner(), playerO);
    }

    TEST_F(TicTacToeTest, DrawCondition)
    {
        // Simulate a draw condition
        grid->SetCellAt(0, 0, new XPiece(playerX));
        grid->SetCellAt(0, 1, new OPiece(playerO));
        grid->SetCellAt(0, 2, new XPiece(playerX));
        grid->SetCellAt(1, 0, new OPiece(playerO));
        grid->SetCellAt(1, 1, new XPiece(playerX));
        grid->SetCellAt(1, 2, new OPiece(playerO));
        grid->SetCellAt(2, 0, new OPiece(playerO));
        grid->SetCellAt(2, 1, new XPiece(playerX));
        grid->SetCellAt(2, 2, new OPiece(playerO));

        EXPECT_TRUE(game->IsDrawCondition());
        EXPECT_FALSE(game->IsWinningCondition());
    }

    TEST_F(TicTacToeTest, InvalidMove)
    {
        unsigned char row = 0, col = 0;
        EXPECT_TRUE(game->TryMakeMove(row, col));
        game->SwitchPlayer();

        // Attempt to place 'O' at the same spot
        EXPECT_FALSE(game->TryMakeMove(row, col));
    }

    TEST_F(TicTacToeTest, SwitchPlayer)
    {
        unsigned char row = 0, col = 0;
        game->TryMakeMove(row, col);
        EXPECT_EQ(game->GetCurrentPlayer().ptr->GetPlayerName(), playerX->GetPlayerName());

        game->SwitchPlayer();
        EXPECT_EQ(game->GetCurrentPlayer().ptr->GetPlayerName(), playerO->GetPlayerName());
    }

}

int main(int argc, char **argv)
{
    DURLIB::Log::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
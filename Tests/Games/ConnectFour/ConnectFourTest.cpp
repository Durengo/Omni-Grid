#include <gtest/gtest.h>

#include <durlib.h>
#include <ogrid.h>

namespace OGRID
{
    class ConnectFourTest : public ::testing::Test
    {
    protected:
        ConnectFour *game;
        GameConfiguration *config;
        Grid *grid;
        Player *playerR;
        Player *playerB;

        void SetUp() override
        {
            playerR = new Player("Red", PlayerType::Human, 0);
            playerB = new Player("Black", PlayerType::Human, 1);

            game = new ConnectFour();
            game->SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                               .setGameName("ConnectFour")
                                               .setGameDescription("ConnectFour Game")
                                               .setGrid(6, 7)
                                               .setMaxPlayers(2)
                                               .addPlayer(playerR)
                                               .addPlayer(playerB)
                                               .build());

            config = game->GetGameConfiguration();
            grid = config->grid;

            PlayerNameAndPtr playerRNameAndPtr =
                    {
                            playerR->GetPlayerName(),
                            playerR};

            PlayerNameAndPtr playerBNameAndPtr =
                    {
                            playerB->GetPlayerName(),
                            playerB};

            std::vector<PlayerNameAndPtr> playerPairs =
                    {
                            playerRNameAndPtr,
                            playerBNameAndPtr};

            game->SetPlayerPairs(playerPairs);

            game->SetCurrentPlayer(playerRNameAndPtr);

            game->SetGameStateChecker(new GameStateChecker(new ConnectFourStateCheck()));
        }

        void TearDown() override
        {
            delete game;
            delete config;
            delete grid;
            delete playerR;
            delete playerB;
        }
    };

    TEST_F(ConnectFourTest, TryMakeMove){
        // Simulate a move
        unsigned char row = 0, col = 0;
        game->TryMakeMove(row, col);
        // Piece should fall down to the first unoccupied cell starting from the bottom
        EXPECT_EQ(grid->GetPieceAt(5, 0)->GetRepresentation(), "R");
        EXPECT_EQ(grid->GetPieceAt(5, 0)->GetOwner()->GetSide(), 0);
        EXPECT_EQ(grid->GetPieceAt(0, 0), nullptr);
    }

    TEST_F(ConnectFourTest, VerticalWin)
    {
        // Simulate a vertical winning condition
        for (int i = 0; i < 4; ++i)
        {
            unsigned char col = 0, row = 0;
            game->TryMakeMove(row, col);
        }

        EXPECT_TRUE(game->IsWinningCondition());
        EXPECT_EQ(game->GetWinner(), playerR);
    }

    TEST_F(ConnectFourTest, HorizontalWin)
    {
        // Simulate a horizontal winning condition
        for (int i = 0; i < 4; ++i)
        {
            unsigned char row = 0, col = i;
            game->TryMakeMove(row, col);
        }

        EXPECT_TRUE(game->IsWinningCondition());
        EXPECT_EQ(game->GetWinner(), playerR);
    }

    TEST_F(ConnectFourTest, DiagonalWin)
    {
        // Simulate a diagonal winning condition
        for (int i = 0; i < 4; ++i)
        {
            unsigned char row = i, col = i;
            game->TryMakeMove(row, col);
        }

        EXPECT_TRUE(game->IsWinningCondition());
        EXPECT_EQ(game->GetWinner(), playerR);
    }

    TEST_F(ConnectFourTest, DrawCondition)
    {
        // Fill the entire grid without a winning condition
        for (int i = 1; i <= grid->GetRows(); ++i)
        {
            unsigned char row = 0, col;
            if (i % 3 == 0){
                std::vector<unsigned char> columns = {1, 0, 3, 2, 5, 4, 6};
                for (unsigned char colI : columns) {
                    game->TryMakeMove(row, colI);
                    game->SwitchPlayer();
                }
            } else {
                for (int j = 0; j < grid->GetCols(); ++j) {
                    col = j;
                    game->TryMakeMove(row, col);
                    game->SwitchPlayer();
                }
            }
        }

        EXPECT_TRUE(game->IsDrawCondition());
        EXPECT_FALSE(game->IsWinningCondition());
    }

    TEST_F(ConnectFourTest, InvalidMove)
    {
        unsigned char row = 0, col = 0;
        for (int i = 1; i <= 6; ++i) {
            game->TryMakeMove(row, col);
            if (i % 3 == 0) {
                game->SwitchPlayer();
            }
        }

        // Attempt to place piece on fully occupied column
        EXPECT_FALSE(game->TryMakeMove(row, col));
    }
}

int main(int argc, char **argv)
{
    DURLIB::Log::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <gtest/gtest.h>

#include <durlib.h>
#include <ogrid.h>

namespace OGRID
{
    class CheckersTest : public ::testing::Test
    {
    protected:
        Checkers *game;
        GameConfiguration *config;
        Grid *grid;
        Player *playerW;
        Player *playerB;

        void SetUp() override
        {
            playerW = new Player("White", PlayerType::Human, 0);
            playerB = new Player("Black", PlayerType::Human, 1);

            game = new Checkers();
            game->SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                               .setGameName("Checkers")
                                               .setGameDescription("Checkers Game")
                                               .setGrid(8, 8)  // Standard Checkers grid size
                                               .setMaxPlayers(2)
                                               .addPlayer(playerW)
                                               .addPlayer(playerB)
                                               .build());

            config = game->GetGameConfiguration();
            grid = config->grid;

            PlayerNameAndPtr playerWNameAndPtr =
                    {
                            playerW->GetPlayerName(),
                            playerW};

            PlayerNameAndPtr playerBNameAndPtr =
                    {
                            playerB->GetPlayerName(),
                            playerB};

            std::vector<PlayerNameAndPtr> playerPairs =
                    {
                            playerWNameAndPtr,
                            playerBNameAndPtr};

            game->SetPlayerPairs(playerPairs);

            game->SetCurrentPlayer(playerWNameAndPtr);

            game->SetGameStateChecker(new GameStateChecker(new CheckersStateCheck()));
        }

        void TearDown() override
        {
            delete game;
            delete config;
            delete grid;
            delete playerW;
            delete playerB;
        }
    };

    TEST_F(CheckersTest, TryMakeMove)
    {
        game->SetupBoard();
        // Select the piece
        unsigned char row = 5, col = 0;
        game->TryMakeMove(row, col);

        // Move the piece
        row = 4, col = 1;
        ASSERT_TRUE(game->TryMakeMove(row, col));
        ASSERT_EQ(grid->GetPieceAt(5, 0), nullptr);
        ASSERT_EQ(grid->GetPieceAt(4, 1)->GetRepresentation(), "W");
    }

    TEST_F(CheckersTest, TryMakeAttackMove)
    {
        grid->SetPieceAt(2, 3, new WhitePieceCheckers(playerW));
        game->AddPieceToPieceManager(grid->GetPieceAt(2, 3), {3, 2});
        grid->SetPieceAt(1, 2, new BlackPieceCheckers(playerB));
        game->AddPieceToPieceManager(grid->GetPieceAt(1, 2), {2, 1});

        // Select the piece
        unsigned char row = 2, col = 3;
        game->TryMakeMove(row, col);

        row = 0, col = 1;
        ASSERT_TRUE(game->TryMakeMove(row, col));
        ASSERT_EQ(grid->GetPieceAt(2, 3), nullptr);
        ASSERT_EQ(grid->GetPieceAt(1, 2), nullptr);
        ASSERT_EQ(grid->GetPieceAt(0, 1)->GetRepresentation(), "W");
    }

    TEST_F(CheckersTest, WinningCondition)
    {
        grid->SetPieceAt(2, 3, new WhitePieceCheckers(playerW));
        game->AddPieceToPieceManager(grid->GetPieceAt(2, 3), {3, 2});
        grid->SetPieceAt(1, 2, new BlackPieceCheckers(playerB));
        game->AddPieceToPieceManager(grid->GetPieceAt(1, 2), {2, 1});

        // Select the piece
        unsigned char row = 2, col = 3;
        game->TryMakeMove(row, col);

        row = 0, col = 1;
        ASSERT_TRUE(game->TryMakeMove(row, col));
        // White wins
        ASSERT_EQ(game->GetGameStateChecker()->CheckWin(grid), 0);
        game->SwitchPlayer();

        // Reset the board
        game->RemovePieceFromPieceManager(grid->GetPieceAt(0, 1));
        grid->SetPieceAt(0, 1, nullptr, true);

        grid->SetPieceAt(0, 1, new BlackPieceCheckers(playerB));
        game->AddPieceToPieceManager(grid->GetPieceAt(0, 1), {1, 0});
        grid->SetPieceAt(1, 2, new WhitePieceCheckers(playerW));
        game->AddPieceToPieceManager(grid->GetPieceAt(1, 2), {2, 1});

        // Select the piece
        row = 0, col = 1;
        game->TryMakeMove(row, col);

        row = 2, col = 3;
        ASSERT_TRUE(game->TryMakeMove(row, col));
        // Black wins
        ASSERT_EQ(game->GetGameStateChecker()->CheckWin(grid), 1);
    }

    TEST_F(CheckersTest, InvalidMove)
    {
        grid->SetPieceAt(2, 3, new WhitePieceCheckers(playerW));
        game->AddPieceToPieceManager(grid->GetPieceAt(2, 3), {3, 2});

        // Select the piece
        unsigned char row = 2, col = 3;
        game->TryMakeMove(row, col);

        row = 5, col = 3;
        ASSERT_FALSE(game->TryMakeMove(row, col));
    }
}

int main(int argc, char **argv)
{
    DURLIB::Log::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

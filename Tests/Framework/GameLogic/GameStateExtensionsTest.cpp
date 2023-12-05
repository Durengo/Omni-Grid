#include <gtest/gtest.h>

#include <durlib.h>

#include "Grid/Grid.h"
#include "Player/Piece.h"
#include "GameLogicImplementation/GameStateExtensions.h"

namespace OGRID
{
    class GameStateExtensionsTest : public ::testing::Test
    {
    protected:
        Grid *grid;

        void SetUp() override
        {
            grid = new Grid(3, 3);
        }

        void TearDown() override
        {
            delete grid;
        }
    };

    TEST_F(GameStateExtensionsTest, CheckForRecurringStringInRow)
    {
        Grid grid(3, 3);
        Piece pieceX("X", nullptr);
        GameStateExtensions extensions;

        // Set up the grid
        grid.SetPieceAt(0, 0, &pieceX);
        grid.SetPieceAt(0, 1, &pieceX);
        grid.SetPieceAt(0, 2, &pieceX);

        EXPECT_TRUE(extensions.CheckForRecurringStringInRow(&grid, "X", 3));
        EXPECT_FALSE(extensions.CheckForRecurringStringInRow(&grid, "X", 4));
    }

    TEST_F(GameStateExtensionsTest, CheckForRecurringStringInCol)
    {
        Grid grid(3, 3);
        Piece pieceX("X", nullptr);
        GameStateExtensions extensions;

        // Set up the grid
        grid.SetPieceAt(0, 0, &pieceX);
        grid.SetPieceAt(1, 0, &pieceX);
        grid.SetPieceAt(2, 0, &pieceX);

        EXPECT_TRUE(extensions.CheckForRecurringStringInCol(&grid, "X", 3));
        EXPECT_FALSE(extensions.CheckForRecurringStringInCol(&grid, "X", 4));
    }

    TEST_F(GameStateExtensionsTest, CheckForRecurringStringInDiagonal)
    {
        Grid grid(3, 3);
        Piece pieceX("X", nullptr);
        GameStateExtensions extensions;

        // Set up the grid
        grid.SetPieceAt(0, 0, &pieceX);
        grid.SetPieceAt(1, 1, &pieceX);
        grid.SetPieceAt(2, 2, &pieceX);

        EXPECT_TRUE(extensions.CheckForRecurringStringInDiagonal(&grid, "X", 3));
        EXPECT_FALSE(extensions.CheckForRecurringStringInDiagonal(&grid, "X", 4));
    }

}

int main(int argc, char **argv)
{
    DURLIB::Log::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
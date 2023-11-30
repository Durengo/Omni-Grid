#include <gtest/gtest.h>
#include "Grid/Grid.h"
#include "Player/Piece.h"

namespace OGRID
{
    // Test fixture for Grid
    class GridTest : public ::testing::Test
    {
    protected:
        Grid *grid;
        Piece *defaultPiece;

        void SetUp() override
        {
            defaultPiece = new Piece("X", nullptr);
            grid = new Grid(3, 3, defaultPiece);
        }

        void TearDown() override
        {
            delete grid;
            delete defaultPiece;
        }
    };

    TEST_F(GridTest, Constructor)
    {
        EXPECT_EQ(grid->GetRows(), 10);
        EXPECT_EQ(grid->GetCols(), 10);
    }

    // More test cases follow...
}

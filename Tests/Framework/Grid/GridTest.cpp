#include <gtest/gtest.h>

#include <durlib.h>

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
            grid = new Grid(3, 3);
        }

        void TearDown() override
        {
            delete grid;
            delete defaultPiece;
        }
    };

    TEST_F(GridTest, Constructor)
    {
        EXPECT_EQ(grid->GetRows(), 3);
        EXPECT_NE(grid->GetRows(), 10);
        EXPECT_EQ(grid->GetCols(), 3);
        EXPECT_NE(grid->GetCols(), 10);

        EXPECT_EQ(grid->GetDefaultPiece(), nullptr);
        EXPECT_NE(grid->GetDefaultPiece(), defaultPiece);

        EXPECT_EQ(grid->GetPieceAt(0, 0), nullptr);
        EXPECT_NE(grid->GetPieceAt(0, 0), defaultPiece);

        EXPECT_EQ(grid->GetCellAt(0, 0)->m_Piece, nullptr);

        EXPECT_EQ(grid->GetLastChangedChar(), std::make_pair(0, 0));
    }

    TEST_F(GridTest, Exceptions)
    {
        EXPECT_THROW(grid->GetPieceAt(10, 10), std::out_of_range);
        EXPECT_THROW(grid->GetCellAt(10, 10), std::out_of_range);

        EXPECT_THROW(grid->SetPieceAt(10, 10, defaultPiece), std::out_of_range);
        EXPECT_THROW(grid->SetCellAt(10, 10, defaultPiece), std::out_of_range);
        EXPECT_THROW(grid->SetCellAt(10, 10, grid->GetCellAt(0, 0)), std::out_of_range);

        EXPECT_THROW(grid->SetPieceAt(0, 0, nullptr), std::invalid_argument);
        EXPECT_THROW(grid->SetCellAt(0, 0, (Piece *)nullptr), std::invalid_argument);
        EXPECT_THROW(grid->SetCellAt(0, 0, (Cell *)nullptr), std::invalid_argument);

        EXPECT_NO_THROW(grid->SetPieceAt(0, 0, nullptr, true));
        EXPECT_NO_THROW(grid->SetCellAt(0, 0, (Piece *)nullptr, true));
        EXPECT_NO_THROW(grid->SetCellAt(0, 0, (Cell *)nullptr, true));

        EXPECT_NO_THROW(grid->SetPieceAt(0, 0, defaultPiece));
    }

    // More test cases follow...
}

int main(int argc, char **argv)
{
    DURLIB::Log::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
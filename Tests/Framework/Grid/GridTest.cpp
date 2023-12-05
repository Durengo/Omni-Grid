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

    // It is important to segregate exception tests, as they cause other tests to fail.
    // That doesn't mean that there isn't a design issue here. But it's not a priority.

    TEST_F(GridTest, ExceptionsOOF1)
    {
        EXPECT_THROW(grid->GetPieceAt(10, 10), std::out_of_range);
        EXPECT_THROW(grid->GetCellAt(10, 10), std::out_of_range);
    }

    TEST_F(GridTest, ExceptionsOOF2)
    {
        EXPECT_THROW(grid->SetPieceAt(10, 10, defaultPiece), std::out_of_range);
        EXPECT_THROW(grid->SetCellAt(10, 10, defaultPiece), std::out_of_range);
        EXPECT_THROW(grid->SetCellAt(10, 10, grid->GetCellAt(0, 0)), std::out_of_range);
    }

    TEST_F(GridTest, ExceptionsOOF3)
    {
        EXPECT_THROW(grid->SetPieceAt(0, 0, nullptr), std::invalid_argument);
        EXPECT_THROW(grid->SetCellAt(0, 0, (Piece *)nullptr), std::invalid_argument);
        EXPECT_THROW(grid->SetCellAt(0, 0, (Cell *)nullptr), std::invalid_argument);
    }

    TEST_F(GridTest, NoExceptions1)
    {
        EXPECT_THROW(grid->SetPieceAt(10, 10, defaultPiece), std::out_of_range);
        EXPECT_THROW(grid->SetCellAt(10, 10, defaultPiece), std::out_of_range);
        EXPECT_THROW(grid->SetCellAt(10, 10, grid->GetCellAt(0, 0)), std::out_of_range);
    }

    TEST_F(GridTest, NoExceptions2)
    {
        EXPECT_NO_THROW(grid->SetPieceAt(0, 0, nullptr, true));
        EXPECT_NO_THROW(grid->SetCellAt(0, 0, (Piece *)nullptr, true));
        EXPECT_NO_THROW(grid->SetCellAt(0, 0, (Cell *)nullptr, true));
    }
    // EXPECT_THROW(grid->SetPieceAt(0, 0, defaultPiece), std::runtime_error);
    TEST_F(GridTest, NoExceptions3)
    {
        EXPECT_NO_THROW(grid->SetPieceAt(0, 0, defaultPiece));
    }

    TEST_F(GridTest, InitializationWithDefaultPiece)
    {
        Piece *initPiece = new Piece("O", nullptr);
        Grid initGrid(5, 5, initPiece);
        for (unsigned char i = 0; i < 5; ++i)
        {
            for (unsigned char j = 0; j < 5; ++j)
            {
                EXPECT_EQ(initGrid.GetPieceAt(i, j), initPiece);
            }
        }
        delete initPiece;
    }

    TEST_F(GridTest, GridResizing)
    {
        grid->ResetGridWithNewSize(5, 5);
        EXPECT_EQ(grid->GetRows(), 5);
        EXPECT_EQ(grid->GetCols(), 5);
    }

    TEST_F(GridTest, ResetGridFunctionality)
    {
        grid->SetPieceAt(1, 1, defaultPiece);
        grid->ResetGrid();
        EXPECT_EQ(grid->GetPieceAt(1, 1), nullptr);
    }

    TEST_F(GridTest, SetGridWithDifferentSizes)
    {
        std::vector<std::vector<Cell *>> newGrid(4, std::vector<Cell *>(4, nullptr));
        grid->SetGrid(newGrid);
        EXPECT_EQ(grid->GetRows(), 4);
        EXPECT_EQ(grid->GetCols(), 4);
    }

    TEST_F(GridTest, OutOfBoundsAccess)
    {
        EXPECT_THROW(grid->SetPieceAt(10, 10, defaultPiece), std::out_of_range);
        EXPECT_THROW(grid->SetCellAt(10, 10, new Cell()), std::out_of_range);
    }

    TEST_F(GridTest, GridStringRepresentation)
    {
        grid->SetPieceAt(0, 0, defaultPiece);
        std::string actual = grid->GetGridAsString();
        std::string expected = "X|NULL|NULL\n"
                               "NULL|NULL|NULL\n"
                               "NULL|NULL|NULL";
        EXPECT_EQ(actual, expected);
    }

    TEST_F(GridTest, LastChangedCharacterTracking)
    {
        grid->SetPieceAt(2, 2, defaultPiece);
        auto lastChanged = grid->GetLastChangedChar();
        EXPECT_EQ(lastChanged.first, 2);
        EXPECT_EQ(lastChanged.second, 2);
    }

    TEST_F(GridTest, OperatorOverloads)
    {
        auto &row = (*grid)[1];
        row[1]->m_Piece = defaultPiece;
        EXPECT_EQ(grid->GetPieceAt(1, 1), defaultPiece);
    }

    TEST_F(GridTest, SetGridExceptionHandling)
    {
        std::vector<std::vector<Cell *>> emptyGrid;
        EXPECT_THROW(grid->SetGrid(emptyGrid), std::invalid_argument);
    }

    TEST_F(GridTest, GridCellUpdate)
    {
        grid->SetPieceAt(1, 1, defaultPiece);
        EXPECT_EQ(grid->GetPieceAt(1, 1), defaultPiece);
    }

}

int main(int argc, char **argv)
{
    DURLIB::Log::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
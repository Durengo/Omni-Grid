#include "GameStateChecker.h"

#include "Grid/Grid.h"

namespace OGRID
{
    GameStateChecker::GameStateChecker(IGameState *strategy)
        : m_GameState(strategy)
    {
    }

    GameStateChecker::~GameStateChecker()
    {
        delete m_GameState;
    }

    int GameStateChecker::CheckWin(Grid *grid) const
    {
        return m_GameState->CheckWin(grid);
    }

    bool GameStateChecker::IsDraw(Grid *grid) const
    {
        return m_GameState->IsDraw(grid);
    }

    bool GameStateChecker::IsColumnOccupied(Grid *grid, unsigned char colToCheck, unsigned char &rowToFill) {
        // Iterate through the column from bottom to top
        for (int row = grid->GetRows() - 1; row >= 0; --row)
        {
            if (grid->GetPieceAt(row, colToCheck) == nullptr)
            {
                // Found an empty spot in the column
                rowToFill = static_cast<unsigned char>(row);
                return false;
            }
        }

        // Column is fully occupied
        return true;
    }

    unsigned char GameStateChecker::GetTopMostPiecePositionInColumn(Grid *grid, int col)
    {
        // Go down the column
        for (unsigned char row = 0; row < grid->GetRows(); ++row)
        {
            if (grid->GetPieceAt(row, col) != nullptr)
            {
                // Found the first piece
                return row;
            }
        }
        // Column is empty
        return static_cast<unsigned char>(grid->GetRows());
    }
}
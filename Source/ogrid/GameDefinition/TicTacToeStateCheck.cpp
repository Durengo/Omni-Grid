#include "TicTacToeStateCheck.h"

#include <typeinfo>

namespace OGRID
{

    int TicTacToeStateCheck::CheckWin(Grid *grid) const
    {
        // To use CheckForRecurringPieceX we must bind side number to piece type.
        // We can do this by creating a map of side number to piece type. Or just hardcode ¯\_(ツ)_/¯.
        // But this will not work at the moment since we are using only one class to define all pieces.
        // This needs more work as the methods get the base type <Piece> instead of the derived type <XPiece> or <OPiece> from the grid cell.

        // if (m_GameStateExtensions.CheckForRecurringPieceInRow(grid, typeid(XPiece), 3) || m_GameStateExtensions.CheckForRecurringPieceInCol(grid, typeid(XPiece), 3) ||
        //     m_GameStateExtensions.CheckForRecurringPieceInDiagonal(grid, typeid(XPiece), 3) || m_GameStateExtensions.CheckForRecurringPieceInAntiDiagonal(grid, typeid(XPiece), 3))
        // {
        //     // 'X' wins
        //     return 0;
        // }
        // if (m_GameStateExtensions.CheckForRecurringPieceInRow(grid, typeid(OPiece), 3) || m_GameStateExtensions.CheckForRecurringPieceInCol(grid, typeid(OPiece), 3) ||
        //     m_GameStateExtensions.CheckForRecurringPieceInDiagonal(grid, typeid(OPiece), 3) || m_GameStateExtensions.CheckForRecurringPieceInAntiDiagonal(grid, typeid(OPiece), 3))
        // {
        //     // 'O' wins
        //     return 0;
        // }

        // If the above doesn't work, fall back to using strings.
        if (m_GameStateExtensions.CheckForRecurringStringInRow(grid, "X", 3) || m_GameStateExtensions.CheckForRecurringStringInCol(grid, "X", 3) ||
            m_GameStateExtensions.CheckForRecurringStringInDiagonal(grid, "X", 3) || m_GameStateExtensions.CheckForRecurringStringInAntiDiagonal(grid, "X", 3))
        {
            // 'X' wins
            return 0;
        }
        if (m_GameStateExtensions.CheckForRecurringStringInRow(grid, "O", 3) || m_GameStateExtensions.CheckForRecurringStringInCol(grid, "O", 3) ||
            m_GameStateExtensions.CheckForRecurringStringInDiagonal(grid, "O", 3) || m_GameStateExtensions.CheckForRecurringStringInAntiDiagonal(grid, "O", 3))
        {
            // 'O' wins
            return 1;
        }

        // No winner
        return -1;
    }

    bool TicTacToeStateCheck::IsDraw(Grid *grid) const
    {
        return m_GameStateExtensions.CheckIfAllSpotsFilled(grid);
    }
}
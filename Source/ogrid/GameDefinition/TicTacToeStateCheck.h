#pragma once

#include <typeinfo>

#include "IGameState.h"

#include "GameDefinition/GameStateExtensions.h"
#include "GameDefinition/TicTacToePieces.h"

namespace OGRID
{
    class TicTacToeStateCheck : public IGameState
    {
    public:
        int CheckWin(Grid *grid) const override
        {
            // To use CheckForRecurringPieceX we must bind side number to piece type.
            // We can do this by creating a map of side number to piece type. Or just hardcode ¯\_(ツ)_/¯.
            // But this will not work at the moment since we are using only one class to define all pieces.
            // This needs more work as the methods get the base type <Piece> instead of the derived type <XPiece> or <OPiece> from the grid cell.

            // if (GameStateExtensions::CheckForRecurringPieceInRow(grid, typeid(XPiece), 3) || GameStateExtensions::CheckForRecurringPieceInCol(grid, typeid(XPiece), 3) ||
            //     GameStateExtensions::CheckForRecurringPieceInDiagonal(grid, typeid(XPiece), 3) || GameStateExtensions::CheckForRecurringPieceInAntiDiagonal(grid, typeid(XPiece), 3))
            // {
            //     // 'X' wins
            //     return 0;
            // }
            // if (GameStateExtensions::CheckForRecurringPieceInRow(grid, typeid(OPiece), 3) || GameStateExtensions::CheckForRecurringPieceInCol(grid, typeid(OPiece), 3) ||
            //     GameStateExtensions::CheckForRecurringPieceInDiagonal(grid, typeid(OPiece), 3) || GameStateExtensions::CheckForRecurringPieceInAntiDiagonal(grid, typeid(OPiece), 3))
            // {
            //     // 'O' wins
            //     return 0;
            // }

            // If the above doesn't work, fall back to using strings.
            if (GameStateExtensions::CheckForRecurringStringInRow(grid, "X", 3) || GameStateExtensions::CheckForRecurringStringInCol(grid, "X", 3) ||
                GameStateExtensions::CheckForRecurringStringInDiagonal(grid, "X", 3) || GameStateExtensions::CheckForRecurringStringInAntiDiagonal(grid, "X", 3))
            {
                // 'X' wins
                return 0;
            }
            if (GameStateExtensions::CheckForRecurringStringInRow(grid, "O", 3) || GameStateExtensions::CheckForRecurringStringInCol(grid, "O", 3) ||
                GameStateExtensions::CheckForRecurringStringInDiagonal(grid, "O", 3) || GameStateExtensions::CheckForRecurringStringInAntiDiagonal(grid, "O", 3))
            {
                // 'O' wins
                return 1;
            }

            // No winner
            return -1;
        }

        bool IsDraw(Grid *grid) const override
        {
            return GameStateExtensions::CheckIfAllSpotsFilled(grid);
        }
    };
}
#pragma once

#include <string>
#include <typeinfo>

#include "Grid/grid.h"
#include "GameDefinition/Piece.h"

/*
Checking for class type of pieces would look like this:
CheckForRecurringPieceInRow(typeid(XPiece), 3))
*/
namespace OGRID
{
    // Forward declarations
    // class Grid;
    // class Piece;

    class GameStateExtensions
    {
    public:
        bool CheckForRecurringStringInRow(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const;
        bool CheckForRecurringPieceInRow(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const;

        bool CheckForRecurringStringInCol(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const;
        bool CheckForRecurringPieceInCol(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const;

        bool CheckForRecurringStringInDiagonal(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const;
        bool CheckForRecurringPieceInDiagonal(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const;

        bool CheckForRecurringStringInAntiDiagonal(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const;
        bool CheckForRecurringPieceInAntiDiagonal(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const;

        bool CheckIfAllSpotsFilled(Grid *grid) const;
    };
}
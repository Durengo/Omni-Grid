#pragma once

#include "MoveRule.h"

// Grid representation of the move on the board, e.g.
/*
    K, Q - Move Definition
    KING MOVE:
    . X .
    X K X
    . X .
    QUEEN MOVE:
    . X .
    X Q X
    . X .
*/

namespace OGRID
{
    class PawnMoveRule : public MoveRule
    {
    public:
        bool IsValidMove(const Grid &grid, unsigned char startRow, unsigned char startCol, unsigned char endRow, unsigned char endCol) const override
        {
            // Example: Pawn can move forward one space if unoccupied
            if (startCol == endCol)
            {
                if (grid.GetStringAt(endRow, endCol) == grid.GetDefaultString())
                {
                    // Check if the destination is unoccupied
                    // logic to check if the move is forward by one space
                    if (true)
                    {
                        return true;
                    }
                }
            }

            // Add logic for diagonal captures, double move on first turn, etc.

            // If none of the conditions are met, the move is invalid
            return false;
        }
    };
}
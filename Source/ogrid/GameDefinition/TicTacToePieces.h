#pragma once

#include "GameDefinition/MoveRule.h"

#include "GameDefinition/Piece.h"
#include "Grid/Grid.h"

namespace OGRID
{
    class XMoveRule : public MoveRule
    {
    public:
        // We only need to check if the end cell is unoccupied, as there is no concept of a "start" cell in tic tac toe.
        bool IsValidMove(const Grid &grid, unsigned char startRow, unsigned char startCol, unsigned char endRow, unsigned char endCol) const override
        {
            return grid.GetPieceAt(endRow, endCol) == nullptr;
        }
    };

    class OMoveRule : public MoveRule
    {
        // We only need to check if the end cell is unoccupied, as there is no concept of a "start" cell in tic tac toe.
        bool IsValidMove(const Grid &grid, unsigned char startRow, unsigned char startCol, unsigned char endRow, unsigned char endCol) const override
        {
            return grid.GetPieceAt(endRow, endCol) == nullptr;

            // Piece *startCellPiece = grid.GetPieceAt(startRow, startCol);
            // Piece *endCellPiece = grid.GetPieceAt(endRow, endCol);

            // if (startCellPiece == nullptr)
            // {
            //     return false;
            // }
            // // Start cell must be occupied by an O
            // if (startCellPiece->GetRepresentation() != "O")
            // {
            //     return false;
            // }
            // // Check if the end cell is unoccupied
            // if (endCellPiece != nullptr)
            // {
            //     return false;
            // }
            // return true;
        }
    };
}
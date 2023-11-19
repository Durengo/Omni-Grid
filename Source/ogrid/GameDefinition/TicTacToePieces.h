#pragma once

#include "GameDefinition/MoveRule.h"

#include "GameDefinition/Piece.h"
#include "Grid/Grid.h"

// TODO: It might be better to define specific exception instead of returning booleans, except for the case of invalid moves.

namespace OGRID
{
    class XMoveRule : public MoveRule
    {
    public:
        // We only need to check if the end cell is unoccupied, as there is no concept of a "start" cell in tic tac toe.
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override
        {
            return grid->GetPieceAt(toX, toY) == nullptr;
        }
    };

    class OMoveRule : public MoveRule
    {
        // We only need to check if the end cell is unoccupied, as there is no concept of a "start" cell in tic tac toe.
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override
        {
            return grid->GetPieceAt(toX, toY) == nullptr;

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

    class XPiece : public Piece
    {
    public:
        XPiece(Player *player)
            : Piece("X", player)
        {
            this->AddMoveRule(new XMoveRule());
        }
    };

    class OPiece : public Piece
    {
    public:
        OPiece(Player *player)
            : Piece("O", player)
        {
            this->AddMoveRule(new OMoveRule());
        }
    };
}
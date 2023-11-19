#pragma once

#include "GameDefinition/MoveRule.h"
#include "GameDefinition/Piece.h"

// TODO: It might be better to define specific exception instead of returning booleans, except for the case of invalid moves.

namespace OGRID
{
    class Grid;

    class XMoveRule : public MoveRule
    {
    public:
        // We only need to check if the end cell is unoccupied, as there is no concept of a "start" cell in tic tac toe.
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override;
    };

    class OMoveRule : public MoveRule
    {
        // We only need to check if the end cell is unoccupied, as there is no concept of a "start" cell in tic tac toe.
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override;
    };

    class XPiece : public Piece
    {
    public:
        XPiece(Player *player);
    };

    class OPiece : public Piece
    {
    public:
        OPiece(Player *player);
    };
}
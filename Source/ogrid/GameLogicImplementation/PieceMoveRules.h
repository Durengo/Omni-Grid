#pragma once

#include "GameLogicInterface/IMoveRule.h"
#include "Player/Piece.h"

namespace OGRID{

    class SimplePlaceMoveRule : public IMoveRule
    {
    public:
        // We only need to check if the end cell is unoccupied, as there is no concept of a "start" cell in tic tac toe.
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override;
    };
}
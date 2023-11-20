//
// Created by LastWeek on 20/11/2023.
//

#include "PieceMoveRules.h"

#include "Grid/Grid.h"

namespace OGRID{

    bool SimplePlaceMoveRule::IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
    {
        return grid->GetPieceAt(toX, toY) == nullptr;
    }
}
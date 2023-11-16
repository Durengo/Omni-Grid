#pragma once

#include "MoveRules.h"

namespace OGRID
{
    class UnoccupiedCellRule : public SimpleMoveRule
    {
    public:
        bool IsValidMove(const Grid &grid, unsigned char row, unsigned char col) const override;
    };
}
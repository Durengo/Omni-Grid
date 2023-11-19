#pragma once

#include "MoveRules.h"

namespace OGRID
{
    class UnoccupiedCellRule : public SimpleMoveRule
    {
    public:
        bool IsValidMoveTo(const Grid &grid, unsigned char row, unsigned char col) const override;
    };
}
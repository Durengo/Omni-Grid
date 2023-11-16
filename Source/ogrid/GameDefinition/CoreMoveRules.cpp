#include "CoreMoveRules.h"

namespace OGRID
{
    bool UnoccupiedCellRule::IsValidMove(const Grid &grid, unsigned char row, unsigned char col) const
    {
        return grid.GetStringAt(row, col) == grid.GetDefaultString();
    }
}
#pragma once

#include "Grid/Grid.h"

namespace OGRID
{
    // class Grid;

    class MoveRule
    {
    public:
        virtual bool IsValidMove(const Grid &grid, unsigned char row, unsigned char col) const = 0;
        virtual bool IsValidMove(const Grid &grid, unsigned char startRow, unsigned char startCol, unsigned char endRow, unsigned char endCol) const = 0;
    };

    class UnoccupiedCellRule : public MoveRule
    {
    public:
        bool IsValidMove(const Grid &grid, unsigned char row, unsigned char col) const override
        {
            return grid.GetStringAt(row, col) == grid.GetDefaultString();
        }
    };
}
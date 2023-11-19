#pragma once

#include "Grid/Grid.h"

namespace OGRID
{
    // class Grid;

    class BaseMoveRule
    {
    public:
        virtual bool IsValidMoveTo(const Grid &grid, unsigned char row, unsigned char col) const = 0;
        virtual bool IsValidMoveFromTo(const Grid &grid, unsigned char startRow, unsigned char startCol, unsigned char endRow, unsigned char endCol) const = 0;
    };

    class SimpleMoveRule : public BaseMoveRule
    {
    public:
        // Default implementation for complex move, assuming it's not applicable for simple rules.
        bool IsValidMoveFromTo(const Grid &grid, unsigned char startRow, unsigned char startCol, unsigned char endRow, unsigned char endCol) const override
        {
            // Simple rules don't use start and end positions
            return false;
        }
    };

    class ComplexMoveRule : public BaseMoveRule
    {
    public:
        // Pure virtual function for simple move, as complex rules require start and end positions.
        virtual bool IsValidMoveTo(const Grid &grid, unsigned char row, unsigned char col) const = 0;
    };
}
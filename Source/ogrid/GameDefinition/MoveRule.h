#pragma once

namespace OGRID
{
    class Grid;

    class MoveRule
    {
    public:
        virtual ~MoveRule() {}
        virtual bool IsValidMove(const Grid &grid, unsigned char startRow, unsigned char startCol, unsigned char endRow, unsigned char endCol) const = 0;
    };
}
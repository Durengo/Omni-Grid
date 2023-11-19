#pragma once

namespace OGRID
{
    // Forward declarations
    class Grid;

    class IGameState
    {
    public:
        virtual ~IGameState() {}
        // Returns side number of the winner. If less than 0, then there is no winner. We have a specific method for that checking draw.
        virtual int CheckWin(const Grid &grid) const = 0;
        virtual bool IsDraw(const Grid &grid) const = 0;
    };
}
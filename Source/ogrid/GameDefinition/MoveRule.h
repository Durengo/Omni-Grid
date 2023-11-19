#pragma once

namespace OGRID
{
    class Grid;

    class MoveRule
    {
    public:
        virtual ~MoveRule() {}
        // ALL MOVES REQUIRE START AND END COORDINATES. BUT MAKE SURE THAT THE COORDINATE YOU WANT TO PLACE YOUR PIECE AT IS THE END COORDINATES.
        virtual bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const = 0;
    };
}
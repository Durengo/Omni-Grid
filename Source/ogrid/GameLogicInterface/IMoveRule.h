#pragma once

namespace OGRID
{
    class Grid;

    class IMoveRule
    {
    public:
        virtual ~IMoveRule() {}
        // ALL MOVES REQUIRE START <from> AND END <to> COORDINATES. BUT MAKE SURE THAT THE COORDINATE YOU WANT TO PLACE YOUR PIECE AT IS THE END <to> COORDINATES.
        virtual bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const = 0;
    };
}
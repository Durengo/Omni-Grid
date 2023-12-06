#pragma once

/**
 * @file IMoveRule.h
 * @brief Contains the IMoveRule class
 * @date 2023-12-06
 */

namespace OGRID
{
    class Grid;

    /**
     * @brief The IMoveRule class. Used to check if the move is valid.
     * @details It contains the strategy to check if the move is valid.
     * @date 2023-12-06
     */
    class IMoveRule
    {
    public:
        /**
         * @brief Destroy the IMoveRule object.
         * @date 2023-12-06
         */
        virtual ~IMoveRule() {}

        /**
         * @brief Check if the move is valid.
         * @details Check if the move is valid using the strategy.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param fromX The x coordinate of the piece.
         * @param fromY The y coordinate of the piece.
         * @param toX The x coordinate of the piece to be attacked.
         * @param toY The y coordinate of the piece to be attacked.
         * @return True if the move is valid, false otherwise.
         */
        // ALL MOVES REQUIRE START <from> AND END <to> COORDINATES. BUT MAKE SURE THAT THE COORDINATE YOU WANT TO PLACE YOUR PIECE AT IS THE END <to> COORDINATES.
        virtual bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const = 0;
    };
}
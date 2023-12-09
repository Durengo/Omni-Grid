#pragma once

/**
 * @file IGameState.h
 * @brief Contains the IGameState class
 * @date 2023-12-06
 */

namespace OGRID
{
    // Forward declarations
    class Grid;

    /**
     * @brief The IGameState class. Used to check the state of the game.
     * @details It contains the strategy to check the state of the game.
     * @date 2023-12-06
     */
    class IGameState
    {
    public:
        /**
         * @brief Destroy the IGameState object.
         * @date 2023-12-06
         */
        virtual ~IGameState() {}

        /**
         * @brief Check if the game is over.
         * @details Check if the game is over using the strategy.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @return True if the game is over, false otherwise.
         */
        // Returns side number of the winner. If less than 0, then there is no winner. We have a specific method for that checking draw.
        virtual int CheckWin(Grid *grid) const = 0;

        /**
         * @brief Check if the game is a draw.
         * @details Check if the game is a draw using the strategy.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @return True if the game is a draw, false otherwise.
         */
        virtual bool IsDraw(Grid *grid) const = 0;
    };
}
#pragma once

/**
 * @file IGameState.h
 * @brief Contains the IGameState class
 * @date 2023-12-06
 */

namespace OGRID
{
    class Grid;

    /**
     * @brief The IGameState class. Used to check the state of the game.
     * @details It contains the strategy to check the state of the game.
     * @date 2023-12-06
     */
    class IAttackRule
    {
    public:
        /**
         * @brief Destroy the IGameState object.
         * @date 2023-12-06
         */
        virtual ~IAttackRule() {}

        /**
         * @brief Check if the attack is valid.
         * @details Check if the attack is valid using the strategy.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param x The x coordinate of the piece.
         * @param y The y coordinate of the piece.
         * @param x2 The x coordinate of the piece to be attacked.
         * @param y2 The y coordinate of the piece to be attacked.
         * @param canContinue shows if there's another attack available after this one.
         * @return True if the attack is valid, false otherwise.
         */
        // canContinue shows if there's another attack available after this one.
        virtual bool IsValidAttack(Grid *grid, int x, int y, int x2, int y2, bool &canContinue) const = 0;
    };
}
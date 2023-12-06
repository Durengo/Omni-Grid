#pragma once

#include "GameLogicInterface/IGameState.h"
#include "GameLogicImplementation/GameStateExtensions.h"

/**
 * @file TicTacToeStateCheck.h
 * @brief TicTacToe state check
 * @date 2023-12-06
 */

namespace OGRID
{
    /**
     * @brief TicTacToe state check
     * @details Check if the game has a winning condition or a draw condition.
     * @date 2023-12-06
     * @see IGameState
     * @see GameStateExtensions
     */
    class TicTacToeStateCheck : public IGameState
    {
    private:
        /**
         * @brief TicTacToe state check
         * @date 2023-12-06
         */
        GameStateExtensions m_GameStateExtensions = GameStateExtensions();

    public:
        /**
         * @brief Check if the game has a winning condition
         * @date 2023-12-06
         * @param grid Grid to check
         * @return the side that won
         * @see Player
         */
        int CheckWin(Grid *grid) const override;

        /**
         * @brief Check if the game has a draw condition
         * @date 2023-12-06
         * @param grid Grid to check
         * @return true If the game has a draw condition, false otherwise
         */

        bool IsDraw(Grid *grid) const override;
    };
}
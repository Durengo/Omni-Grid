#pragma once

#include "GameLogicInterface/IGameState.h"

/**
 * @file GameStateChecker.h
 * @brief Contains the GameStateChecker class
 * @date 2023-12-06
 */

/*
How to use:
GameStateChecker gameStateCheckerTicTacToe(new TicTacToeStateCheck());
*/

namespace OGRID
{
    /**
     * @brief The GameStateChecker class. Used to check the state of the game.
     * @details It contains the strategy to check the state of the game.
     * @date 2023-12-06
     */
    class GameStateChecker
    {
    private:
        /**
         * @brief The strategy to check the state of the game.
         * @details It is used to check the state of the game.
         * @date 2023-12-06
         */
        IGameState *m_GameState;

    public:
        /**
         * @brief Construct a new GameStateChecker object.
         * @details Construct a new GameStateChecker object using the strategy to check the state of the game.
         * @date 2023-12-06
         */
        GameStateChecker(IGameState *strategy);

        /**
         * @brief Destroy the GameStateChecker object.
         * @date 2023-12-06
         */
        ~GameStateChecker();

        /**
         * @brief Check the state of the game.
         * @details Check the state of the game using the strategy.
         * @date 2023-12-06
         */
        int CheckWin(Grid *grid) const;

        /**
         * @brief Check if the game is a draw.
         * @details Check if the game is a draw using the strategy.
         * @date 2023-12-06
         */
        bool IsDraw(Grid *grid) const;

        /**
         * @brief Check if the game is over.
         * @details Check if the game is over using the strategy.
         * @date 2023-12-06
         */
        bool IsColumnOccupied(Grid *grid, unsigned char colToCheck, unsigned char &rowToFill);

        /**
         * @brief Get the top most piece position in a column.
         * @details Get the top most piece position in a column using the strategy.
         * @date 2023-12-06
         */
        unsigned char GetTopMostPiecePositionInColumn(Grid *grid, int col);
    };
}
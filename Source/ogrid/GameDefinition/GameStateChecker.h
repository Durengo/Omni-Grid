#pragma once

#include "GameDefinition/IGameState.h"

/*
How to use:
GameStateChecker gameStateCheckerTicTacToe(new TicTacToeStateCheck());
*/

namespace OGRID
{
    class GameStateChecker
    {
    private:
        IGameState *m_GameState;

    public:
        GameStateChecker(IGameState *strategy)
            : m_GameState(strategy)
        {
        }

        ~GameStateChecker()
        {
            delete m_GameState;
        }

        bool CheckWin(const Grid &grid) const
        {
            return m_GameState->CheckWin(grid);
        }

        bool IsDraw(const Grid &grid) const
        {
            return m_GameState->IsDraw(grid);
        }
    };
}
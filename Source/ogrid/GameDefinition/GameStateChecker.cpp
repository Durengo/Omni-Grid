#include "GameStateChecker.h"

namespace OGRID
{
    GameStateChecker::GameStateChecker(IGameState *strategy)
        : m_GameState(strategy)
    {
    }

    GameStateChecker::~GameStateChecker()
    {
        delete m_GameState;
    }

    int GameStateChecker::CheckWin(Grid *grid) const
    {
        return m_GameState->CheckWin(grid);
    }

    bool GameStateChecker::IsDraw(Grid *grid) const
    {
        return m_GameState->IsDraw(grid);
    }
}
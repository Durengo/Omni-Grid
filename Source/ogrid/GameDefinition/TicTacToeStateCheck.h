#pragma once

#include "IGameState.h"
#include "GameDefinition/GameStateExtensions.h"

namespace OGRID
{
    class TicTacToeStateCheck : public IGameState
    {
    private:
        GameStateExtensions m_GameStateExtensions = GameStateExtensions();

    public:
        int CheckWin(Grid *grid) const override;

        bool IsDraw(Grid *grid) const override;
    };
}
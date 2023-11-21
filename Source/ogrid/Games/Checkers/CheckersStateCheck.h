#pragma once

#include "GameLogicInterface/IGameState.h"
#include "GameLogicImplementation/GameStateExtensions.h"

namespace OGRID
{
    class CheckersStateCheck : public IGameState
    {
    private:
        GameStateExtensions m_GameStateExtensions = GameStateExtensions();

    public:
        int CheckWin(Grid *grid) const override;

        bool IsDraw(Grid *grid) const override;
    };
}
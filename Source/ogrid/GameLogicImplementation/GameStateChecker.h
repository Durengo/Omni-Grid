#pragma once

#include "GameLogicInterface/IGameState.h"

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
        GameStateChecker(IGameState *strategy);

        ~GameStateChecker();

        int CheckWin(Grid *grid) const;

        bool IsDraw(Grid *grid) const;

        bool IsColumnOccupied(Grid *grid, unsigned char colToCheck, unsigned char &rowToFill);

        unsigned char GetTopMostPiecePositionInColumn(Grid *grid, int col);
    };
}
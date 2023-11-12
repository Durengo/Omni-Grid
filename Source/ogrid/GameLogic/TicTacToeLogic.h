#pragma once

#include <durlib.h>
#include <mutex>
#include "../../Generics/IGameLogic.h"
#include "../../Sandbox/Player/Player.h"
#include "../../Sandbox/Player/Moves.h"

namespace Sandbox
{
    class TicTacToeLogic : public GENERICS::IGameLogic
    {
    private:
        static bool m_randomizeTurnOrder;

        // Constructors & Destructors
    public:
        TicTacToeLogic();
        ~TicTacToeLogic();

        // Constructors & Destructors

        // Game Logic Implementation
    public:
        void SetRandomizeTurnOrder(bool randomize);

    private:
        static void ResetGrid();

        static void ResetPlayers();

        static void PrintPlayersTurnOrder();

        // Public methods
    public:
        static void SetupGame();

        static void ResetGame();

        static void StartGame();

        static void MakeMove(unsigned char row, unsigned char col);

        void SwapPlayerPositions();
    };
}

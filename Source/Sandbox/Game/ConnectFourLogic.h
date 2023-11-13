#pragma once

#include <GameLogic/IGameLogic.h>


namespace OGRIDSandbox
{
    class ConnectFourLogic : public OGRID::IGameLogic
    {
    private:
        static bool m_randomizeTurnOrder;

    public:
        ConnectFourLogic();
        ~ConnectFourLogic();

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

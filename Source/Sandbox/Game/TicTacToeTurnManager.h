#pragma once

#include <GameLogic/ITurnManager.h>

namespace OGRIDSandbox
{
    class TicTacToeTurnManager : public OGRID::ITurnManager
    {
    public:
        // Constructors & Destructors
        TicTacToeTurnManager(const std::vector<OGRID::PlayerNameAndPtr> &players);
        TicTacToeTurnManager() = default;
        ~TicTacToeTurnManager();

        // Private methods:
    private:
        bool IsWinningCondition(OGRID::Grid *grid, unsigned char row, unsigned char col) override;
        bool IsWinningCondition(OGRID::Grid *grid, char playerChar) override;
        bool IsDrawCondition(OGRID::Grid *grid, unsigned char row, unsigned char col) override;

        // Public methods:
    public:
        void SetupPlayers(OGRID::GameConfiguration *gameConfiguration, const std::vector<OGRID::MoveType> &moveTypes, bool randomize) override;

        bool MakeMove(OGRID::Grid *grid, unsigned char row, unsigned char col) override;
    };
}
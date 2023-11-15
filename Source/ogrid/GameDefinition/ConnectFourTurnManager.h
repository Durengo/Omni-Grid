#pragma once

#include <GameLogic/ITurnManager.h>

namespace OGRIDSandbox
{
    class ConnectFourTurnManager : public OGRID::ITurnManager
    {
    public:
        // Constructors & Destructors
        ConnectFourTurnManager(const std::vector<OGRID::PlayerNameAndPtr> &players);
        ConnectFourTurnManager() = default;
        ~ConnectFourTurnManager();

        // Private methods:
    private:
        bool IsWinningCondition(OGRID::Grid *grid, unsigned char row, unsigned char col) override;
        bool IsWinningCondition(OGRID::Grid *grid, char playerChar) override;
        bool IsDrawCondition(OGRID::Grid *grid, unsigned char row, unsigned char col) override;

        // Specific to this game logic
        bool IsColumnOccupied(OGRID::Grid *grid, unsigned char colToCheck, unsigned char &rowToFill);

        // Public methods:
    public:
        void SetupPlayers(OGRID::GameConfiguration *gameConfiguration, const std::vector<OGRID::MoveType> &moveTypes, bool randomize) override;

        bool MakeMove(OGRID::Grid *grid, unsigned char row, unsigned char col) override;
    };
}

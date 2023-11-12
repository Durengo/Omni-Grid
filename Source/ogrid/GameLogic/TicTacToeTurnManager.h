#pragma once

#include "../../Generics/ITurnManager.h"
#include "../../Sandbox//Grid/Grid.h"
#include "../../Sandbox/Player/Player.h"
#include "../../Sandbox/Game/GameConfiguration.h"

namespace Sandbox
{
    class TicTacToeTurnManager : public GENERICS::ITurnManager
    {
    public:
        // Constructors & Destructors
        TicTacToeTurnManager(const std::vector<GENERICS::PlayerNameAndPtr> &players);
        TicTacToeTurnManager() = default;
        ~TicTacToeTurnManager();

        // Private methods:
    private:
        bool IsWinningCondition(GENERICS::Grid *grid, unsigned char row, unsigned char col) override;
        bool IsWinningCondition(GENERICS::Grid *grid, char playerChar) override;
        bool IsDrawCondition(GENERICS::Grid *grid, unsigned char row, unsigned char col) override;

        // Public methods:
    public:
        void SetupPlayers(GENERICS::GameConfiguration *gameConfiguration, const std::vector<GENERICS::MoveType> &moveTypes, bool randomize) override;

        bool MakeMove(GENERICS::Grid *grid, unsigned char row, unsigned char col) override;
    };
}
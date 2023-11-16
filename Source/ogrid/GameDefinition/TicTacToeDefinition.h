#pragma once

#include <memory>

#include "Grid/Grid.h"
#include "MoveType.h"
#include "MoveRules.h"
#include "Player.h"
#include "AbstractGameLogic.h"

namespace OGRID
{
    class TicTacToeDefinition : public AbstractGameLogic
    {
    private:
        // Constructor and Destructor
    public:
        TicTacToeDefinition();
        ~TicTacToeDefinition();
        // Private methods
    private:
        void InitializeGame() override;
        void DeinitializeGame() override;
        // Public methods
    public:
        void MakeMove(Player &player) override;

        void CheckConditions() override;

        void ResetGame() override;

        void EndGame() override;
    };

}
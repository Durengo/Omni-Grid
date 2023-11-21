#pragma once

#include "GameLogicInterface/IGame.h"

namespace OGRID
{
    class ConnectFour : public IGame
    {
        // Variables for alpha of circles
        float alpha = 1.0f;
        // Speed of the transition
        float alphaSpeed = 0.025f;

    public:
        ConnectFour() = default;
        ~ConnectFour() = default;

        bool TryMakeMove(unsigned char &row, unsigned char &col) override;
        bool IsWinningCondition() override;
        bool IsDrawCondition() override;
        void SetupPlayers() override;

        void Initialize() override;
        void OnGUIUpdateGrid() override;
        void OnGUIUpdateGridHover(Vector2 cell) override;

    private:
        void DrawCircle(int row, int col, Color color, bool blinking = false);
    };
}

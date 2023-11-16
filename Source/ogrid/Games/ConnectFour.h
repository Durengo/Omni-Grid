#pragma once

#include <GameLogic/IGame.h>

namespace OGRID{
    class ConnectFour : public IGame{
        // Variables for alpha of circles
        float alpha = 1.0f;
        float alphaSpeed = 0.025f; // Speed of the transition
    public:
        ConnectFour() = default;
        ~ConnectFour() = default;

        bool TryMakeMove(unsigned char &row, unsigned char &col) override;
        bool IsWinningCondition(unsigned char row, unsigned char col) override;
        bool IsWinningCondition(char playerChar) override;
        bool IsDrawCondition(unsigned char row, unsigned char col) override;
        void SetupPlayers(const std::vector<OGRID::MoveType> &moveTypes) override;

        void Initialize() override;
        void OnGUIUpdateGrid() override;
        void OnGUIUpdateGridHover(Vector2 cell) override;

    private:
        void DrawCircle(int row, int col, Color color, bool blinking = false);
    };
}

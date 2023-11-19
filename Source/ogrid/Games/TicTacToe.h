#pragma once

#include "GameLogic/IGame.h"

namespace OGRID
{
    class TicTacToe : public IGame
    {
    public:
        TicTacToe() = default;
        ~TicTacToe() = default;

        bool TryMakeMove(unsigned char &row, unsigned char &col) override;
        bool IsWinningCondition(unsigned char row, unsigned char col) override;
        bool IsWinningCondition(char playerChar) override;
        bool IsDrawCondition(unsigned char row, unsigned char col) override;
        void SetupPlayers(const std::vector<OGRID::MoveType> &moveTypes) override;

        void Initialize() override;
        void OnGUIUpdateGrid() override;
        void OnGUIUpdateGridHover(Vector2 cell) override;

    private:
        void DrawX(int row, int col);
        void DrawO(int row, int col);
    };
}
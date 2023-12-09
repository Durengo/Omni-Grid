#pragma once

#include "GameLogicInterface/IGame.h"
#include "User/User.h"

namespace OGRID
{
    class Piece;

    class Checkers : public IGame
    {
        // Contains references to super pieces
        std::vector<Piece *> m_Supers;
        // Contains reference to the selected piece
        Piece *m_SelectedPiece = nullptr;
        // Just to keep track of positions
        std::map<std::pair<int, int>, Piece *> m_Pieces;

        // Variables for alpha of circles
        float alpha = 1.0f;
        // Speed of the transition
        float alphaSpeed = 0.025f;

    public:
        Checkers() = default;
        ~Checkers() = default;

        bool TryMakeMove(unsigned char &row, unsigned char &col) override;
        bool IsWinningCondition() override;
        bool IsDrawCondition() override;
        void SetupPlayers() override;

        void Initialize(OGRID::User* user) override;
        void OnGUIUpdateGrid() override;
        void OnGUIUpdateGridHover(Vector2 cell) override;
        void SetupBoard();
        void AddAsSuperPiece(Piece *piece);
        void RemoveSuperPiece(Piece *piece);
        bool IsSuperPiece(Piece *piece);

        void AddPieceToPieceManager(Piece *piece, std::pair<int, int> position);
        void RemovePieceFromPieceManager(Piece *piece);
        void RemovePieceFromPieceManager(std::pair<int, int> position);
    private:
        std::pair<int, int> GetPiecePosition(Piece *piece);
        void SetPiecePosition(Piece *piece, std::pair<int, int> position);

        void DrawPiece(int row, int col, Color color, bool blinking, bool super);
        void DrawCell(int row, int col);
    };
}
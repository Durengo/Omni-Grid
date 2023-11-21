#pragma once

#include "GameLogicInterface/IGame.h"

namespace OGRID
{
    class Piece;

    class Checkers : public IGame
    {
        std::vector<Piece*> m_Supers; // Contains references to super pieces
        Piece* m_SelectedPiece = nullptr; // Contains reference to the selected piece
        std::map<std::pair<int,int>, Piece*> m_Pieces; // Just to keep track of positions

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

        void Initialize() override;
        void OnGUIUpdateGrid() override;
        void OnGUIUpdateGridHover(Vector2 cell) override;

    private:
        void SetupBoard();

        void AddAsSuperPiece(Piece *piece);
        void RemoveSuperPiece(Piece *piece);
        bool IsSuperPiece(Piece *piece);

        void AddPieceToPieceManager(Piece *piece, std::pair<int,int> position);
        void RemovePieceFromPieceManager(Piece *piece);
        void RemovePieceFromPieceManager(std::pair<int,int> position);
        std::pair<int,int> GetPiecePosition(Piece *piece);
        void SetPiecePosition(Piece *piece, std::pair<int,int> position);

        void DrawPiece(int row, int col, Color color, bool blinking, bool super);
        void DrawCell(int row, int col);
    };
}
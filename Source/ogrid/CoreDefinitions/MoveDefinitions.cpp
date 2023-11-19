#include "MoveDefinitions.h"

#include "GameDefinition/Piece.h"
#include "GameDefinition/CoreMoveRules.h"

namespace OGRID
{
    std::vector<Piece *> GetTicTacToePieces()
    {
        std::vector<Piece *> Pieces;

        // Create and add Piece for X
        auto PieceX = new Piece("X");
        PieceX->AddRule(new UnoccupiedCellRule());
        Pieces.push_back(PieceX);

        // Create and add Piece for O
        auto PieceO = new Piece("O");
        PieceO->AddRule(new UnoccupiedCellRule());
        Pieces.push_back(PieceO);

        return Pieces;
    }
}
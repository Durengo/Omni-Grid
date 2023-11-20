#include "TicTacToePieces.h"

#include "Grid/Grid.h"

namespace OGRID
{
    bool SimplePlaceMoveRule::IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
    {
        return grid->GetPieceAt(toX, toY) == nullptr;
    }

    XPiece::XPiece(Player *player)
        : Piece("X", player)
    {
        this->AddMoveRule(new SimplePlaceMoveRule());
    }

    OPiece::OPiece(Player *player)
        : Piece("O", player)
    {
        this->AddMoveRule(new SimplePlaceMoveRule());
    }
}
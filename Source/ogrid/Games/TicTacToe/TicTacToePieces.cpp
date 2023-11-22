#include "TicTacToePieces.h"
#include "GameLogicImplementation/PieceRules.h"

namespace OGRID
{

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
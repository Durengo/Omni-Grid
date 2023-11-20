#include "ConnectFourPieces.h"

#include "Grid/Grid.h"
#include "GameLogicImplementation/PieceMoveRules.h"

namespace OGRID{

    RedPiece::RedPiece(Player *player)
            : Piece("R", player)
    {
        this->AddMoveRule(new SimplePlaceMoveRule());
    }

    BlackPiece::BlackPiece(Player *player)
            : Piece("B", player)
    {
        this->AddMoveRule(new SimplePlaceMoveRule());
    }
}
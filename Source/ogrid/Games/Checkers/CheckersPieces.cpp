#include "CheckersPieces.h"
#include "GameLogicImplementation/PieceRules.h"

namespace OGRID
{
    WhitePieceCheckers::WhitePieceCheckers(Player *player) :
    Piece("W", player)
    {
        this->AddMoveRule(new NormalCheckersMoveRule());
        this->AddAttackRule(new JumpNormalCheckersAttackRule());
    }

    BlackPieceCheckers::BlackPieceCheckers(Player *player) :
    Piece("B", player)
    {
        this->AddMoveRule(new NormalCheckersMoveRule());
        this->AddAttackRule(new JumpNormalCheckersAttackRule());
    }
}
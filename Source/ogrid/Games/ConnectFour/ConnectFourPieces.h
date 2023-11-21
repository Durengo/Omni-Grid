#pragma once

#include "GameLogicInterface/IMoveRule.h"
#include "Player/Piece.h"

namespace OGRID
{
    class Grid;

    class RedPiece : public Piece
    {
    public:
        RedPiece(Player *player);
    };

    class BlackPiece : public Piece
    {
    public:
        BlackPiece(Player *player);
    };
}
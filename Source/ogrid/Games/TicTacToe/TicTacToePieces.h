#pragma once

#include "GameLogicInterface/IMoveRule.h"
#include "Player/Piece.h"

// TODO: It might be better to define specific exception instead of returning booleans, except for the case of invalid moves.

namespace OGRID
{
    class Grid;

    class XPiece : public Piece
    {
    public:
        XPiece(Player *player);
    };

    class OPiece : public Piece
    {
    public:
        OPiece(Player *player);
    };
}
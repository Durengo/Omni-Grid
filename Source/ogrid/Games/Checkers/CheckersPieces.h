#pragma once

#include <Player/Piece.h>

namespace OGRID
{
    class Player;
    class Grid;

    class WhitePieceCheckers : public Piece
    {
    public:
        WhitePieceCheckers(Player *player);
    };

    class BlackPieceCheckers : public Piece
    {
    public:
        BlackPieceCheckers(Player *player);
    };
}
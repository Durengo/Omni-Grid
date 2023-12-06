#pragma once

#include "GameLogicInterface/IMoveRule.h"
#include "Player/Piece.h"

// TODO: It might be better to define specific exception instead of returning booleans, except for the case of invalid moves.

/**
 * @file TicTacToePieces.h
 * @brief TicTacToe pieces
 * @date 2023-12-06
 */

namespace OGRID
{
    class Grid;

    /**
     * @brief TicTacToe X piece
     * @date 2023-12-06
     */
    class XPiece : public Piece
    {
    public:
        XPiece(Player *player);
    };

    /**
     * @brief TicTacToe O piece
     * @date 2023-12-06
     */
    class OPiece : public Piece
    {
    public:
        OPiece(Player *player);
    };
}
#pragma once

#include <string>
#include <vector>

#include "GameLogicInterface/IMoveRule.h"
#include "Player/Player.h"

namespace OGRID
{
    class Piece
    {
    protected:
        // String representation of the move (char), like (chess) "K" for king, "Q" for queen, etc.
        std::string m_representation;

        // Rules for this move type
        std::vector<IMoveRule *> m_moveRules;

        // Owner of this piece
        Player *m_owner;

    public:
        Piece(std::string rep, Player *player);

        ~Piece();

        void AddMoveRule(IMoveRule *rule);

        const std::string &GetRepresentation() const;

        const Player *GetOwner() const;

        bool isValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const;
    };
}
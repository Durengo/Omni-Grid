#pragma once

#include <string>
#include <vector>

#include <GameLogicInterface/IAttackRule.h>
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

        // Rules for attacking
        std::vector<IAttackRule *> m_attackRules;

        // Owner of this piece
        Player *m_owner;

    public:
        Piece(std::string rep, Player *player);

        ~Piece();

        void AddMoveRule(IMoveRule *rule);

        void AddAttackRule(IAttackRule *rule);

        const std::string &GetRepresentation() const;

        const Player *GetOwner() const;

        bool isValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const;

        bool isValidAttack(Grid *grid, int fromX, int fromY, int toX, int toY, bool &canContinue) const;
    };
}
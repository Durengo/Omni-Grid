#pragma once

#include <string>
#include <vector>

#include "MoveRule.h"
#include "Player/Player.h"

namespace OGRID
{
    // class Grid;
    // class Player;

    class Piece
    {
    protected:
        // String representation of the move (char), like (chess) "K" for king, "Q" for queen, etc.
        std::string m_representation;

        // Rules for this move type
        std::vector<MoveRule *> m_moveRules;

        // Owner of this piece
        Player *m_owner;

    public:
        Piece(std::string rep, Player *player) : m_representation(rep), m_owner(player) {}

        ~Piece()
        {
            // Delete all MoveRule objects
            for (auto rule : m_moveRules)
            {
                delete rule;
            }
            // DO NOT DELETE m_owner
        }

        void AddMoveRule(MoveRule *rule)
        {
            m_moveRules.push_back(rule);
        }

        const std::string &GetRepresentation() const
        {
            return m_representation;
        }

        const Player *GetOwner() const
        {
            return m_owner;
        }

        bool isValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
        {
            bool isValid = false;

            // We would have to check all the rules for this piece, but I think this will need more refinement to work in such a manner.
            for (const auto &rule : m_moveRules)
            {
                isValid = rule->IsValidMove(grid, fromX, fromY, toX, toY);
            }

            return isValid;
        }
    };
}
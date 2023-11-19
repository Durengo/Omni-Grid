#pragma once

#include <string>
#include <vector>

#include "MoveRule.h"

namespace OGRID
{
    // class Grid;

    class Piece
    {
    protected:
        // String representation of the move (char), like (chess) "K" for king, "Q" for queen, etc.
        std::string m_representation;

        // Rules for this move type
        std::vector<MoveRule *> moveRules;

    public:
        Piece(std::string rep) : m_representation(rep) {}

        ~Piece()
        {
            // Delete all MoveRule objects
            for (auto rule : moveRules)
            {
                delete rule;
            }
        }

        void AddMoveRule(MoveRule *rule)
        {
            moveRules.push_back(rule);
        }

        const std::string &GetRepresentation() const
        {
            return m_representation;
        }

        bool isValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
        {
            for (const auto &rule : moveRules)
            {
                if (rule->IsValidMove(grid, fromX, fromY, toX, toY))
                {
                    return true;
                }
            }
            return false;
        }
    };
}
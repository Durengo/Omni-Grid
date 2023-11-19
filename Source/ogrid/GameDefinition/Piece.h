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

        virtual ~Piece()
        {
            // Delete all MoveRule objects
            for (auto rule : moveRules)
            {
                delete rule;
            }
        }

        virtual void AddMoveRule(MoveRule *rule)
        {
            moveRules.push_back(rule);
        }

        virtual const std::string &GetRepresentation() const
        {
            return m_representation;
        }

        virtual bool isValidMove(const Grid &grid, unsigned char startRow, unsigned char startCol, unsigned char endRow, unsigned char endCol) const
        {
            for (const auto &rule : moveRules)
            {
                if (rule->IsValidMove(grid, startRow, startCol, endRow, endCol))
                {
                    return true;
                }
            }
            return false;
        }
    };
}
#pragma once

#include <string>
#include <vector>
#include <memory>

#include "MoveRule.h"

namespace OGRID
{
    // class Grid;

    class MoveType
    {
    private:
        // String representation of the move (char), like (chess) "K" for king, "Q" for queen, etc.
        std::string m_representation;

        // Rules for this move type
        std::vector<std::unique_ptr<MoveRule>> moveRules;

    public:
        MoveType(std::string rep) : m_representation(rep) {}

        void AddRule(std::unique_ptr<MoveRule> rule)
        {
            moveRules.push_back(std::move(rule));
        }

        const std::string &GetRepresentation() const
        {
            return m_representation;
        }

        bool ApplyMove(Grid &grid, unsigned char row, unsigned char col)
        {
            // Check and apply move rules
            for (auto &rule : moveRules)
            {
                if (!rule->IsValidMove(grid, row, col))
                {
                    return false;
                }
            }
            grid.SetStringAt(row, col, m_representation);
            return true;
        }
    };
}
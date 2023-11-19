#pragma once

#include <string>
#include <vector>

#include "MoveRules.h"

namespace OGRID
{
    // class Grid;

    class Piece
    {
    private:
        // String representation of the move (char), like (chess) "K" for king, "Q" for queen, etc.
        std::string m_representation;

        // Rules for this move type
        std::vector<BaseMoveRule *> moveRules;

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

        void AddRule(BaseMoveRule *rule)
        {
            moveRules.push_back(rule);
        }

        const std::string &GetRepresentation() const
        {
            return m_representation;
        }

        // Use this to create low-level move rules which might use both simple and complex moves
        bool ApplyBaseMove(Grid &grid, unsigned char startRow, unsigned char startCol, unsigned char endRow, unsigned char endCol)
        {
            return false;
        }

        // Method to apply a simple move
        bool ApplySimpleMove(Grid &grid, unsigned char row, unsigned char col)
        {
            // TODO: Check move rule type. If it's a complex move, skip...
            for (auto rule : moveRules)
            {
                if (!rule->IsValidMoveTo(grid, row, col))
                {
                    return false;
                }
            }
            grid.SetCellAt(row, col, this);
            return true;
        }

        // Method to apply a complex move (involving start and end positions)
        bool ApplyComplexMove(Grid &grid, unsigned char startRow, unsigned char startCol, unsigned char endRow, unsigned char endCol)
        {
            for (auto rule : moveRules)
            {
                if (!rule->IsValidMoveFromTo(grid, startRow, startCol, endRow, endCol))
                {
                    return false;
                }
            }
            // Assuming the move is represented at the end position
            grid.SetCellAt(endRow, endCol, this);
            return true;
        }
    };
}
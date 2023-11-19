#include "Piece.h"

namespace OGRID
{
    Piece::Piece(std::string rep, Player *player) : m_representation(rep), m_owner(player) {}

    Piece::~Piece()
    {
        // Delete all MoveRule objects
        for (auto rule : m_moveRules)
        {
            delete rule;
        }
        // DO NOT DELETE m_owner
    }

    void Piece::AddMoveRule(IMoveRule *rule)
    {
        m_moveRules.push_back(rule);
    }

    const std::string &Piece::GetRepresentation() const
    {
        return m_representation;
    }

    const Player *Piece::GetOwner() const
    {
        return m_owner;
    }

    bool Piece::isValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
    {
        bool isValid = false;

        // We would have to check all the rules for this piece, but I think this will need more refinement to work in such a manner.
        for (const auto &rule : m_moveRules)
        {
            isValid = rule->IsValidMove(grid, fromX, fromY, toX, toY);
        }

        return isValid;
    }
}
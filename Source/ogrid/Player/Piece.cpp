#include "Piece.h"

#include "durlib.h"

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

    void Piece::SetOwner(Player *player)
    {
        CLI_WARN("This should not be used. It is only here for testing purposes.");

        m_owner = player;
    }

    bool Piece::isValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
    {
        bool isValid = false;

        // We would have to check all the rules for this piece, but I think this will need more refinement to work in such a manner.
        for (const auto &rule : m_moveRules)
        {
            isValid = rule->IsValidMove(grid, fromX, fromY, toX, toY);
            if (isValid)
            {
                break;
            }
        }

        return isValid;
    }

    void Piece::AddAttackRule(IAttackRule *rule)
    {
        m_attackRules.push_back(rule);
    }

    bool Piece::isValidAttack(Grid *grid, int fromX, int fromY, int toX, int toY, bool &canContinue) const
    {
        bool isValid = false;

        for (const auto &rule : m_attackRules)
        {
            isValid = rule->IsValidAttack(grid, fromX, fromY, toX, toY, canContinue);
            if (isValid)
            {
                break;
            }
        }

        return isValid;
    }
}
#pragma once

#include "GameLogicInterface/IMoveRule.h"
#include "Player/Piece.h"

namespace OGRID
{

    class SimplePlaceMoveRule : public IMoveRule
    {
    public:
        // We only need to check if the end cell is unoccupied, as there is no concept of a "start" cell in tic tac toe.
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override;
    };

    class NormalCheckersMoveRule : public IMoveRule
    {
    public:
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override;
    };

    class JumpNormalCheckersAttackRule : public IAttackRule
    {
    public:
        bool IsValidAttack(Grid *grid, int fromX, int fromY, int toX, int toY, bool &canContinue) const override;
    };

    class SuperCheckersMoveRule : public IMoveRule
    {
    public:
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override;
    };

    class JumpSuperCheckersAttackRule : public IAttackRule
    {
    public:
        bool IsValidAttack(Grid *grid, int fromX, int fromY, int toX, int toY, bool &canContinue) const override;
    };
}
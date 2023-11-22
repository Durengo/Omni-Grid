#pragma once

namespace OGRID
{
    class Grid;

    class IAttackRule
    {
    public:
        virtual ~IAttackRule() {}
        // canContinue shows if there's another attack available after this one.
        virtual bool IsValidAttack(Grid *grid, int x, int y, int x2, int y2, bool &canContinue) const = 0;
    };
}
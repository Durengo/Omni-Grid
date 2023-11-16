#include "MoveDefinitions.h"

#include "GameDefinition/MoveType.h"
#include "GameDefinition/CoreMoveRules.h"

namespace OGRID
{
    std::vector<MoveType *> GetTicTacToeMoveTypes()
    {
        std::vector<MoveType *> moveTypes;

        // Create and add MoveType for X
        auto moveTypeX = new MoveType("X");
        moveTypeX->AddRule(new UnoccupiedCellRule());
        moveTypes.push_back(moveTypeX);

        // Create and add MoveType for O
        auto moveTypeO = new MoveType("O");
        moveTypeO->AddRule(new UnoccupiedCellRule());
        moveTypes.push_back(moveTypeO);

        return moveTypes;
    }
}
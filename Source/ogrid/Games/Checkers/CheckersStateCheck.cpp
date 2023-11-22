#include "CheckersStateCheck.h"

namespace OGRID
{

    int CheckersStateCheck::CheckWin(Grid *grid) const
    {
        int whiteCount = 0;
        int blackCount = 0;
        for (int x = 0; x < grid->GetCols(); x++)
        {
            for (int y = 0; y < grid->GetRows(); y++)
            {
                if (grid->GetPieceAt(y, x) != nullptr)
                {
                    if (grid->GetPieceAt(y, x)->GetOwner()->GetSide() == 0)
                    {
                        whiteCount++;
                    }
                    else
                    {
                        blackCount++;
                    }
                }
            }
        }
        if (whiteCount == 0)
        {
            return 1;
        }
        else if (blackCount == 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }

    bool CheckersStateCheck::IsDraw(Grid *grid) const
    {
        // No draw in checkers
        return false;
    }
}
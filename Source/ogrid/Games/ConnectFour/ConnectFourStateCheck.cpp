#include "ConnectFourStateCheck.h"

namespace OGRID{

    int ConnectFourStateCheck::CheckWin(Grid *grid) const {
        if (m_GameStateExtensions.CheckForRecurringStringInRow(grid, "R", 4) || m_GameStateExtensions.CheckForRecurringStringInCol(grid, "R", 4) ||
            m_GameStateExtensions.CheckForRecurringStringInDiagonal(grid, "R", 4) || m_GameStateExtensions.CheckForRecurringStringInAntiDiagonal(grid, "R", 4))
        {
            // 'R' wins
            return 0;
        }
        if (m_GameStateExtensions.CheckForRecurringStringInRow(grid, "B", 4) || m_GameStateExtensions.CheckForRecurringStringInCol(grid, "B", 4) ||
            m_GameStateExtensions.CheckForRecurringStringInDiagonal(grid, "B", 4) || m_GameStateExtensions.CheckForRecurringStringInAntiDiagonal(grid, "B", 4))
        {
            // 'B' wins
            return 1;
        }

        // No winner
        return -1;
    }

    bool ConnectFourStateCheck::IsDraw(Grid *grid) const {
        return m_GameStateExtensions.CheckIfAllSpotsFilled(grid);
    }
}


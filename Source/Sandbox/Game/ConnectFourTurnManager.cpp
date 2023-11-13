#include "ConnectFourTurnManager.h"

#include <algorithm>
#include <random>

#include <durlib.h>
#include <ogrid.h>

namespace OGRIDSandbox{

    ConnectFourTurnManager::ConnectFourTurnManager(const std::vector<OGRID::PlayerNameAndPtr> &players) : ITurnManager(
            players) {
    }

    ConnectFourTurnManager::~ConnectFourTurnManager() = default;

    bool ConnectFourTurnManager::IsWinningCondition(OGRID::Grid *grid, unsigned char row, unsigned char col) {
        char playerChar = grid->GetCharAt(row, col);
        return grid->CheckForRecurringCharsInRow(playerChar, 4) || grid->CheckForRecurringCharsInCol(playerChar, 4) ||
               grid->CheckForRecurringCharsInDiagonal(playerChar, 4) || grid->CheckForRecurringCharsInAntiDiagonal(playerChar, 4);
    }

    bool ConnectFourTurnManager::IsWinningCondition(OGRID::Grid *grid, char playerChar) {
        return grid->CheckForRecurringCharsInRow(playerChar, 4) || grid->CheckForRecurringCharsInCol(playerChar, 4) ||
               grid->CheckForRecurringCharsInDiagonal(playerChar, 4) || grid->CheckForRecurringCharsInAntiDiagonal(playerChar, 4);
    }

    bool ConnectFourTurnManager::IsDrawCondition(OGRID::Grid *grid, unsigned char row, unsigned char col) {
        // Check if all spots are filled.
        bool allSpotsFilled = true;
        for (int row = 0; row < grid->GetRows(); ++row)
        {
            for (int col = 0; col < grid->GetCols(); ++col)
            {
                if (grid->GetCharAt(row, col) == grid->GetDefaultChar())
                {
                    allSpotsFilled = false; // Found an empty spot, so not all spots are filled.
                    break;
                }
            }
            if (!allSpotsFilled)
                break;
        }

        // If all spots are filled and there's no win, then it's a draw.
        return allSpotsFilled && !IsWinningCondition(grid, grid->GetLastChangedChar().first, grid->GetLastChangedChar().second);
    }

    void ConnectFourTurnManager::SetupPlayers(OGRID::GameConfiguration *gameConfiguration,
                                              const std::vector<OGRID::MoveType> &moveTypes, bool randomize) {
        size_t allowedPlayers = gameConfiguration->maxPlayers;

        CLI_ASSERT(m_Players.size() > 1, "Player amount exceeds max player amount.");

        if (randomize)
        {
            std::vector<OGRID::MoveType> shuffledMoveTypes = moveTypes;
            std::random_device rd;
            auto rng = std::default_random_engine{rd()};
            std::shuffle(shuffledMoveTypes.begin(), shuffledMoveTypes.end(), rng);

            for (int i = 0; i < m_Players.size(); i++)
            {
                m_Players[i].ptr->SetPlayerMoveType(shuffledMoveTypes[i % shuffledMoveTypes.size()]);
            }

            // Assuming MoveType::X is the MoveType that goes first.
            std::stable_sort(m_Players.begin(), m_Players.end(),
                             [](const OGRID::PlayerNameAndPtr &a, const OGRID::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetPlayerMoveType() == OGRID::MoveType::X;
                             });
        }
        else
        {
            for (int i = 0; i < m_Players.size(); i++)
            {
                m_Players[i].ptr->SetPlayerMoveType(moveTypes[i % moveTypes.size()]);
            }

            std::stable_sort(m_Players.begin(), m_Players.end(),
                             [](const OGRID::PlayerNameAndPtr &a, const OGRID::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetPlayerMoveType() == OGRID::MoveType::X;
                             });
        }
    }

    bool ConnectFourTurnManager::MakeMove(OGRID::Grid *grid, unsigned char row, unsigned char col) {
        // Check if the column is occupied and find the topmost available spot
        if (!IsColumnOccupied(grid, col, row)) {
            CLI_WARN("Cannot make move at column {0}, because it is fully occupied", col);
            return false;
        }

        OGRID::PlayerNameAndPtr currentPlayer = GetCurrentPlayer();

        // Set the player's move in the grid
        grid->SetCharAt(row, col, OGRID::MoveTypeEnumToChar(currentPlayer.ptr->GetPlayerMoveType()));

        // this->operator++();
        return true;
    }

    bool ConnectFourTurnManager::IsColumnOccupied(OGRID::Grid *grid, unsigned char colToCheck, unsigned char &rowToFill) {
        // Iterate through the column from bottom to top
        for (int row = grid->GetRows() - 1; row >= 0; --row) {
            if (grid->GetCharAt(row, colToCheck) == grid->GetDefaultChar()) {
                // Found an empty spot in the column
                rowToFill = static_cast<unsigned char>(row);
                return true;
            }
        }

        // Column is fully occupied
        return false;
    }
}

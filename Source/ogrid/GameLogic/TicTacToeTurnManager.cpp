#include "TicTacToeTurnManager.h"

#include <algorithm>
#include <random>

#include <durlib.h>
#include "../../Sandbox/Player/Moves.h"
#include "../../Sandbox/Game/GameState.h"

namespace Sandbox
{
    // Constructors & Destructors
    TicTacToeTurnManager::TicTacToeTurnManager(const std::vector<GENERICS::PlayerNameAndPtr> &players)
            : ITurnManager(players) {
    }

    TicTacToeTurnManager::~TicTacToeTurnManager()
    = default;

    // Private methods
    bool TicTacToeTurnManager::IsWinningCondition(GENERICS::Grid *grid, unsigned char row, unsigned char col)
    {
        char playerChar = grid->GetCharAt(row, col);
        return grid->CheckForRecurringCharsInRow(playerChar) || grid->CheckForRecurringCharsInCol(playerChar) ||
               grid->CheckForRecurringCharsInDiagonal(playerChar) || grid->CheckForRecurringCharsInAntiDiagonal(playerChar);
    }

    bool TicTacToeTurnManager::IsWinningCondition(GENERICS::Grid *grid, char playerChar)
    {
        return grid->CheckForRecurringCharsInRow(playerChar) || grid->CheckForRecurringCharsInCol(playerChar) ||
               grid->CheckForRecurringCharsInDiagonal(playerChar) || grid->CheckForRecurringCharsInAntiDiagonal(playerChar);
    }

    bool TicTacToeTurnManager::IsDrawCondition(GENERICS::Grid *grid, unsigned char row, unsigned char col)
    {
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

    // Public methods

    void TicTacToeTurnManager::SetupPlayers(GENERICS::GameConfiguration *gameConfiguration, const std::vector<GENERICS::MoveType> &moveTypes, bool randomize = true)
    {
        size_t allowedPlayers = gameConfiguration->maxPlayers;

        CLI_ASSERT(m_Players.size() > 1, "Player amount exceeds max player amount.");

        if (randomize)
        {
            std::vector<GENERICS::MoveType> shuffledMoveTypes = moveTypes;
            std::random_device rd;
            auto rng = std::default_random_engine{rd()};
            std::shuffle(shuffledMoveTypes.begin(), shuffledMoveTypes.end(), rng);

            for (int i = 0; i < m_Players.size(); i++)
            {
                m_Players[i].ptr->SetPlayerMoveType(shuffledMoveTypes[i % shuffledMoveTypes.size()]);
            }

            // Assuming MoveType::X is the MoveType that goes first.
            std::stable_sort(m_Players.begin(), m_Players.end(),
                             [](const GENERICS::PlayerNameAndPtr &a, const GENERICS::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetPlayerMoveType() == GENERICS::MoveType::X;
                             });
        }
        else
        {
            for (int i = 0; i < m_Players.size(); i++)
            {
                m_Players[i].ptr->SetPlayerMoveType(moveTypes[i % moveTypes.size()]);
            }

            std::stable_sort(m_Players.begin(), m_Players.end(),
                             [](const GENERICS::PlayerNameAndPtr &a, const GENERICS::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetPlayerMoveType() == GENERICS::MoveType::X;
                             });
        }
    }

    bool TicTacToeTurnManager::MakeMove(GENERICS::Grid *grid, unsigned char row, unsigned char col)
    {
        CLI_TRACE("Player {0} is making a move at ({1}, {2}).", GetCurrentPlayer().name, row, col);
        char gridChar = grid->GetCharAt(row, col);
        if (grid->GetCharAt(row, col) != grid->GetDefaultChar())
        {
            CLI_WARN("Cannot make move at ({0}, {1}) because it is already occupied by {2}.", row, col, gridChar);
            return false;
        }

        GENERICS::PlayerNameAndPtr currentPlayer = GetCurrentPlayer();

        grid->SetCharAt(row, col, GENERICS::MoveTypeEnumToChar(currentPlayer.ptr->GetPlayerMoveType()));

        // this->operator++();
        return true;
    }
}
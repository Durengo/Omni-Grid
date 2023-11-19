#include "ITurnManager.h"

#include <durlib.h>

#include <Player/Moves.h>
#include <Player/Player.h>
#include <GameLogic/GameState.h>

namespace OGRID
{

    ITurnManager::ITurnManager(const std::vector<OGRID::PlayerNameAndPtr> &players)
    {
        m_Players = players;
    }

    ITurnManager::~ITurnManager()
    {
        for (auto &playerPair : m_Players)
        {
            playerPair.ptr = nullptr;
            delete playerPair.ptr;
        }
    }

    // Getters & Setters
    OGRID::PlayerNameAndPtr ITurnManager::GetCurrentPlayer() const
    {
        return m_Players[m_currentTurn];
    }

    size_t ITurnManager::GetCurrentTurn() const
    {
        return m_currentTurn;
    }

    std::vector<std::string> ITurnManager::GetPlayerNames() const
    {
        std::vector<std::string> playerNames;
        for (const auto &playerPair : m_Players)
        {
            playerNames.push_back(playerPair.name);
        }
        return playerNames;
    }

    std::vector<OGRID::Player *> ITurnManager::GetPlayerPtrs() const
    {
        std::vector<OGRID::Player *> playerPtrs;
        for (const auto &playerPair : m_Players)
        {
            playerPtrs.push_back(playerPair.ptr);
        }
        return playerPtrs;
    }

    OGRID::PlayerNameAndPtr ITurnManager::GetPlayerPair(size_t at) const
    {
        if (at < m_Players.size())
        {
            return m_Players[at];
        }
        else
        {
            throw std::out_of_range("Index out of range in GetPlayerPair");
        }
    }

    std::vector<OGRID::PlayerNameAndPtr> ITurnManager::GetPlayerPairs() const
    {
        return m_Players;
    }

    void ITurnManager::Reset()
    {
        m_currentTurn = 0;
        m_totalTurns = 0;
    }

    void ITurnManager::PrintPlayerMoves() const
    {
        for (const auto &playerPair : m_Players)
        {
            std::string move = MoveTypeEnumToString(playerPair.ptr->GetPlayerMoveType());
            CLI_TRACE("{0} | {1}", playerPair.name, move);
        }
    }

    OGRID::GameOverType
    ITurnManager::CheckGameOverState(OGRID::Grid *grid, unsigned char row, unsigned char col)
    {
        OGRID::PlayerNameAndPtr currentPlayer = GetCurrentPlayer();
        // PlayerNameAndPtr previousPlayer = GetPlayerPair((GetCurrentTurn() - 1) % m_Players.size());

        if (IsWinningCondition(grid, row, col))
        {
            CLI_INFO("Player {0} won the game!", currentPlayer.name);
            return OGRID::GameOverType::Win;
        }
        if (IsDrawCondition(grid, row, col))
        {
            CLI_INFO("The game ended in a draw!");
            return OGRID::GameOverType::Draw;
        }
        CLI_TRACE("Player {0} finished his move.", currentPlayer.name);
        this->operator++();
        CLI_TRACE("Player {0} is now playing.", GetCurrentPlayer().name);
        return OGRID::GameOverType::None;
    }

    void ITurnManager::SwapPlayerPositions()
    {
        if (m_Players.size() == 2)
        {
            std::swap(m_Players[0], m_Players[1]);
        }
        else
        {
            throw std::runtime_error("Cannot swap player positions if there are more than 2 players.");
        }
    }

    void ITurnManager::SetPlayerPairs(const std::vector<OGRID::PlayerNameAndPtr> &players)
    {
        m_Players = players;
    }
}
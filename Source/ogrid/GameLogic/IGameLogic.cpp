#include "IGameLogic.h"

#include <Grid/Grid.h>
#include <Player/Player.h>
#include <GameLogic/GameState.h>
#include <GameLogic/GameConfiguration.h>

namespace OGRID
{
    // Static variables
    GameState IGameLogic::m_gameState{GameState::NotStarted};
    GameOverType IGameLogic::m_gameOverType{GameOverType::None};
    Player *IGameLogic::m_winner{nullptr};
    GameConfiguration *IGameLogic::m_GameConfiguration{nullptr};

    GameState IGameLogic::GetGameState() const
    {
        return m_gameState;
    }

    void IGameLogic::SetGameState(GameState gameState)
    {
        m_gameState = gameState;
    }

    GameOverType IGameLogic::GetGameOverType() const
    {
        return m_gameOverType;
    }

    Player *IGameLogic::GetWinner() const
    {
        return m_winner;
    }

    GameConfiguration *IGameLogic::GetGameConfiguration() const
    {
        DEBUG_ASSERT(m_GameConfiguration, "GameConfiguration not initialized.");

        return m_GameConfiguration;
    }

    void IGameLogic::SetGameConfiguration(GameConfiguration *gameConfiguration)
    {
        m_GameConfiguration = gameConfiguration;
    }

    std::string IGameLogic::GetGameName() const
    {
        CLI_ASSERT(!m_GameConfiguration->gameName.empty(), "Name not initialized.");

        return m_GameConfiguration->gameName;
    }

    Grid *IGameLogic::GetGrid() const
    {
        CLI_ASSERT(m_GameConfiguration->grid, "Grid not initialized.");

        return m_GameConfiguration->grid;
    }

    std::vector<Player *> IGameLogic::GetPlayers() const
    {
        return m_GameConfiguration->players;
    }
}
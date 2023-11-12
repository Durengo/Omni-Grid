#pragma once

#include <durlib.h>

//*************************************************************
// Can't have virtual static methods, so implement them yourself
//*************************************************************

namespace OGRID
{
    // Forward declarations
    enum GameState;
    enum GameOverType;
    class Player;
    struct GameConfiguration;
    class Grid;

    class IGameLogic
    {
    protected:
        static GameState m_gameState;
        static GameOverType m_gameOverType;
        static Player *m_winner;

        static GameConfiguration *m_GameConfiguration;

        // Getters and Setters
    public:
        GameState GetGameState() const;
        void SetGameState(GameState gameState);

        GameOverType GetGameOverType() const;

        Player *GetWinner() const;

        GameConfiguration *GetGameConfiguration() const;
        void SetGameConfiguration(GameConfiguration *gameConfiguration);

        std::string GetGameName() const;

        Grid *GetGrid() const;

        std::vector<Player *> GetPlayers() const;
    };
}

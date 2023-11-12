//
// Created by LastWeek on 11/11/2023.
//
#pragma once

#include <durlib.h>
#include "../Sandbox/Grid/Grid.h"
#include "../Sandbox/Player/Player.h"
#include "../Sandbox/Game/GameState.h"
#include "../Sandbox/Game/GameConfiguration.h"


//*************************************************************
//Can't have virtual static methods, so implement them yourself
//*************************************************************

namespace GENERICS{
    enum GameState;
    enum GameOverType;

    class IGameLogic {
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

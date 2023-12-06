#pragma once

#include <sstream>

#include <raylib.h>

#include "GUI/GUIInfo.h"
#include "GameLogicImplementation/GameStateChecker.h"

// TODO: Keep track of the current player.

namespace OGRID
{
    // Forward declaration
    class GameConfiguration;
    class Player;
    class Grid;
    enum MoveType;
    struct PlayerNameAndPtr;

    enum GameState
    {
        NotStarted = 0,
        InProgress = 1,
        Paused = 2,
        GameOver = 3
    };

    enum GameOverType
    {
        None = 0,
        Win = 1,
        Draw = 2
    };

    class IGame
    {
    public:
        GUIInfo m_guiInfo;
        bool m_randomizeTurnOrder = true;

    protected:
        GameStateChecker *m_currentGameState;
        GameState m_gameState = GameState::NotStarted;
        GameOverType m_gameOverType = GameOverType::None;
        Player *m_winner = nullptr;
        Player *m_currentPlayer = nullptr;
        size_t m_currentTurn = 0;
        unsigned int m_totalTurns = 0;

        GameConfiguration *m_GameConfiguration = nullptr;

        IGame() = default;
        IGame(IGameState *gameStateStrategy, const std::vector<OGRID::PlayerNameAndPtr> &players);
        ~IGame();

    public:
        virtual bool TryMakeMove(unsigned char &row, unsigned char &col) = 0;
        // virtual bool IsWinningCondition(unsigned char row, unsigned char col) = 0;
        // virtual bool IsWinningCondition(char playerChar) = 0;
        // virtual bool IsDrawCondition(unsigned char row, unsigned char col) = 0;
        virtual bool IsWinningCondition() = 0;
        virtual bool IsDrawCondition() = 0;
        // virtual void SetupPlayers(const std::vector<int> &totalValidSides) = 0;
        virtual void SetupPlayers() = 0;
        virtual void Initialize() = 0;
        // Game specific GUI Grid stuff drawing (X and O for Tic Tac Toe for example).
        virtual void OnGUIUpdateGrid() = 0;
        // On hovering over a grid spot.
        virtual void OnGUIUpdateGridHover(Vector2 cell) = 0;

        void SwapPlayerPositions();

        void ResetGrid();

        void ResetPlayers();

        void PrintPlayersTurnOrder() const;

        void SetupGame();

        void ResetGame();

        void StartGame();

        void PrintPlayerMoves() const;

        void MakeMove(unsigned char row, unsigned char col);

        void Reset();

        // Switch player turns forcefully after a move is made. This is added purely for testing purposes.
        void SwitchPlayer();

        OGRID::GameOverType CheckGameOverState(OGRID::Grid *grid, unsigned char row, unsigned char col);

        // void ChangeGridSize();

        // Getters and Setters
        GameState GetGameState() const;
        void SetGameState(GameState gameState);

        GameOverType GetGameOverType() const;

        Player *GetWinner() const;

        GameConfiguration *GetGameConfiguration() const;
        void SetGameConfiguration(GameConfiguration *gameConfiguration);

        std::string GetGameName() const;

        Grid *GetGrid() const;

        std::vector<Player *> GetPlayers() const;

        void SetRandomizeTurnOrder(bool randomize);

        OGRID::PlayerNameAndPtr GetCurrentPlayer() const;

        // This is solely for testing purposes.
        void SetCurrentPlayer(OGRID::PlayerNameAndPtr player);

        size_t GetCurrentTurn() const;

        GameStateChecker *GetGameStateChecker() const;

        void SetGameStateChecker(GameStateChecker *gameStateChecker);

        std::vector<std::string> GetPlayerNames() const;

        std::vector<OGRID::Player *> GetPlayerPtrs() const;

        OGRID::PlayerNameAndPtr GetPlayerPair(size_t at) const;

        std::vector<OGRID::PlayerNameAndPtr> GetPlayerPairs() const;
        void SetPlayerPairs(const std::vector<OGRID::PlayerNameAndPtr> &players);

        void SetGUIInfo(const GUIInfo &guiInfo);
        GUIInfo GetGUIInfo() const;
    };
}
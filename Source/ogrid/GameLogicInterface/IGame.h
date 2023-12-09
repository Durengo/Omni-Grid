#pragma once

#include <sstream>

#include <raylib.h>

#include "GUI/GUIInfo.h"
#include "GameLogicImplementation/GameStateChecker.h"

#include "User/User.h"

// TODO: Keep track of the current player.

/**
 * @file IGame.h
 * @brief Contains the IGame class
 * @date 2023-12-06
 */

namespace OGRID
{
    // Forward declaration
    class GameConfiguration;
    class Player;
    class Grid;
    enum MoveType;
    struct PlayerNameAndPtr;
    class User;

    /**
     * @brief The IGame class. Used to represent a game.
     * @details It contains the name of the game, the description of the game, the grid of the game, the maximum number of players and the players of the game.
     * @date 2023-12-06
     */
    enum GameState
    {
        NotStarted = 0,
        InProgress = 1,
        Paused = 2,
        GameOver = 3
    };

    /**
     * @brief The GameOverType enum. Used to represent the type of game over.
     * @details It contains the type of game over: None, Win or Draw.
     * @date 2023-12-06
     */
    enum GameOverType
    {
        None = 0,
        Win = 1,
        Draw = 2
    };

    /**
     * @brief The IGame class. Used to represent a game.
     * @details It contains the name of the game, the description of the game, the grid of the game, the maximum number of players and the players of the game.
     * @date 2023-12-06
     */
    class IGame
    {
    public:
        /**
         * brief Holds the information of the GUI.
         * @details This is specifically used for raylib.
         * @date 2023-12-06
         */
        GUIInfo m_guiInfo;

        /**
         * @brief To randomize the turn order of the players.
         * @date 2023-12-06
         */
        bool m_randomizeTurnOrder = true;

    protected:
        /**
         * @brief Holds the logic to check the state of the specific game.
         * @details Example: Tic Tac Toe has different rules than Checkers.
         * @date 2023-12-06
         */
        GameStateChecker *m_currentGameState;

        /**
         * @brief The state of the game.
         * @date 2023-12-06
         */
        GameState m_gameState = GameState::NotStarted;

        /**
         * @brief The game loop state of the game.
         * @date 2023-12-06
         */
        GameOverType m_gameOverType = GameOverType::None;

        /**
         * @brief The winner of the game.
         * @date 2023-12-06
         */
        Player *m_winner = nullptr;

        /**
         * @brief The current player of the game.
         * @details This is the current player that is making a move, i.e. the current turn.
         * @date 2023-12-06
         */
        Player *m_currentPlayer = nullptr;

        /**
         * @brief The current turn of the game.
         * @details This is the current turn of the game. It is used to keep track of the current turn, i.e. each Player has a team. Each team has a turn identifier.
         * Example: Tic Tac Toe has 2 players. Player 1 is X and Player 2 is O. Player 1 has a turn identifier of 0 and Player 2 has a turn identifier of 1.
         * @date 2023-12-06
         */
        size_t m_currentTurn = 0;

        /**
         * @brief Keeps the total number of turns.
         * @date 2023-12-06
         * @note This is not used for anything yet.
         */
        unsigned int m_totalTurns = 0;

        /**
         * @brief The GameConfiguration object.
         * @details This stores the most basic information of the game, like the grid, the players, the max players, the name of the game etc.
         * @date 2023-12-06
         */
        GameConfiguration *m_GameConfiguration = nullptr;

        User *m_User = nullptr;

        /**
         * @brief The constructor of the IGame class.
         * @date 2023-12-06
         */
        IGame() = default;

        /**
         * @brief The constructor of the IGame class.
         * @date 2023-12-06
         * @param gameStateStrategy The GameStateChecker object. This should be specific to each game type.
         * @param players The players of the game.
         */
        IGame(IGameState *gameStateStrategy, const std::vector<OGRID::PlayerNameAndPtr> &players);

        /**
         * @brief The destructor of the IGame class.
         * @date 2023-12-06
         */
        ~IGame();

    public:
        /**
         * @brief Try making a move with the current player.
         * @date 2023-12-06
         * @param row The row of the grid.
         * @param col The column of the grid.
         */
        virtual bool TryMakeMove(unsigned char &row, unsigned char &col) = 0;
        // virtual bool IsWinningCondition(unsigned char row, unsigned char col) = 0;
        // virtual bool IsWinningCondition(char playerChar) = 0;
        // virtual bool IsDrawCondition(unsigned char row, unsigned char col) = 0;

        /**
         * @brief Check if the winning condition is met.
         * @date 2023-12-06
         * @return True if the winning condition is met, false otherwise.
         */
        virtual bool IsWinningCondition() = 0;

        /**
         * @brief Check if the draw condition is met.
         * @date 2023-12-06
         * @return True if the draw condition is met, false otherwise.
         */
        virtual bool IsDrawCondition() = 0;
        // virtual void SetupPlayers(const std::vector<int> &totalValidSides) = 0;

        /**
         * @brief Setup the players of the game.
         * @date 2023-12-06
         */
        virtual void SetupPlayers() = 0;

        /**
         * @brief Setup the core of the game.
         * @date 2023-12-06
         */
        virtual void Initialize(OGRID::User *user) = 0;

        /**
         * @brief Update the game's GUI.
         * @date 2023-12-06
         */
        // Game specific GUI Grid stuff drawing (X and O for Tic Tac Toe for example).
        virtual void OnGUIUpdateGrid() = 0;

        /**
         * @brief Update the game's GUI when hovering over a specific Cell.
         * @date 2023-12-06
         * @param cell The cell of the grid.
         * @see Cell
         */
        // On hovering over a grid spot.
        virtual void OnGUIUpdateGridHover(Vector2 cell) = 0;

        /**
         * @brief Switches the current player to the next player.
         * @date 2023-12-06
         */
        void SwapPlayerPositions();

        /**
         * @brief Call the Grid object's ResetGrid() function.
         * @details GameConfiguration must be set before calling this function.
         * @date 2023-12-06
         */
        void ResetGrid();

        /**
         * @brief Reset the players of the game.
         * @date 2023-12-06
         */
        void ResetPlayers();

        /**
         * @brief Print the players of the game.
         * @date 2023-12-06
         */
        void PrintPlayersTurnOrder() const;

        /**
         * @brief Sets up the game.
         * @date 2023-12-06
         */
        void SetupGame();

        /**
         * @brief Resets the game.
         * @date 2023-12-06
         */
        void ResetGame();

        /**
         * @brief Starts the game.
         * @date 2023-12-06
         */
        void StartGame();

        /**
         * @brief Prints the turn order.
         * @date 2023-12-06
         */
        void PrintPlayerMoves() const;

        /**
         * @brief Attempts to make a move.
         * @date 2023-12-06
         */
        void MakeMove(unsigned char row, unsigned char col);

        /**
         * @brief Resets the game.
         */
        void Reset();

        /**
         * @brief Sets the current player to the next player.
         * @date 2023-12-06
         * @note This is solely for testing purposes.
         */
        // Switch player turns forcefully after a move is made. This is added purely for testing purposes.
        void SwitchPlayer();

        /**
         * @brief Checks if the game is over.
         * @date 2023-12-06
         * @return True if the game is over, false otherwise.
         */
        OGRID::GameOverType CheckGameOverState(OGRID::Grid *grid, unsigned char row, unsigned char col);

        // void ChangeGridSize();

        // Getters and Setters
        /**
         * @brief Get the state of the game.
         * @date 2023-12-06
         * @return The state of the game.
         */
        GameState GetGameState() const;

        /**
         * @brief Set the state of the game.
         * @date 2023-12-06
         * @param gameState The state of the game.
         */
        void SetGameState(GameState gameState);

        /**
         * @brief Get the game loop state of the game.
         * @date 2023-12-06
         * @return The game loop state of the game.
         */
        GameOverType GetGameOverType() const;

        /**
         * @brief Get the winner of the game.
         * @date 2023-12-06
         */
        Player *GetWinner() const;

        /**
         * @brief Get the GameConfiguration object.
         * @date 2023-12-06
         * @return The GameConfiguration object.
         */
        GameConfiguration *GetGameConfiguration() const;

        /**
         * @brief Set the GameConfiguration object.
         * @date 2023-12-06
         * @param gameConfiguration The GameConfiguration object.
         */
        void SetGameConfiguration(GameConfiguration *gameConfiguration);

        /**
         * @brief Get the name of the game.
         * @date 2023-12-06
         * @return The name of the game.
         */
        std::string GetGameName() const;

        /**
         * @brief Get the Grid object of the game.
         * @date 2023-12-06
         * @return The Grid object of the game.
         */
        Grid *GetGrid() const;

        /**
         * @brief Get the a Vector of the players of the game.
         * @date 2023-12-06
         * @return Get the a Vector of the players of the game.
         */
        std::vector<Player *> GetPlayers() const;

        /**
         * @brief Toggle the randomization of the turn order.
         * @date 2023-12-06
         * @param randomize True to randomize the turn order, false otherwise.
         */
        void SetRandomizeTurnOrder(bool randomize);

        /**
         * @brief Get the current player of the game.
         * @date 2023-12-06
         * @return The current player of the game.
         */
        OGRID::PlayerNameAndPtr GetCurrentPlayer() const;

        /**
         * @brief Set the current player of the game.
         * @date 2023-12-06
         * @param player The current player of the game.
         * @note This is solely for testing purposes.
         */
        // This is solely for testing purposes.
        void SetCurrentPlayer(OGRID::PlayerNameAndPtr player);

        /**
         * @brief Get the current turn of the game.
         * @date 2023-12-06
         * @return The current turn of the game.
         */
        size_t GetCurrentTurn() const;

        /**
         * @brief Get the current state of the game.
         * @date 2023-12-06
         * @return The current state of the game.
         */
        GameStateChecker *GetGameStateChecker() const;

        /**
         * @brief Set the current state of the game.
         * @date 2023-12-06
         * @param gameStateChecker The current state of the game.
         */
        void SetGameStateChecker(GameStateChecker *gameStateChecker);

        /**
         * @brief Get a Vector of the names of the players from GameConfiguration.
         * @date 2023-12-06
         * @return A Vector of the names of the players from GameConfiguration.
         */
        std::vector<std::string> GetPlayerNames() const;

        /**
         * @brief Get a Vector of the pointers of the players from GameConfiguration.
         * @date 2023-12-06
         * @return A Vector of the pointers of the players from GameConfiguration.
         */
        std::vector<OGRID::Player *> GetPlayerPtrs() const;

        /**
         * @brief Get the name and pointer of the player from GameConfiguration.
         * @date 2023-12-06
         * @param at The index of the player.
         * @return The name and pointer of the player from GameConfiguration.
         */
        OGRID::PlayerNameAndPtr GetPlayerPair(size_t at) const;

        /**
         * @brief Get a Vector of the names and pointers of the players from GameConfiguration.
         * @date 2023-12-06
         * @return A Vector of the names and pointers of the players from GameConfiguration.
         */
        std::vector<OGRID::PlayerNameAndPtr> GetPlayerPairs() const;

        /**
         * @brief Set the names and pointers of the players from GameConfiguration.
         * @date 2023-12-06
         * @param players A Vector of the names and pointers of the players from GameConfiguration.
         */
        void SetPlayerPairs(const std::vector<OGRID::PlayerNameAndPtr> &players);

        /**
         * @brief Get the GUIInfo object.
         * @date 2023-12-06
         * @return The GUIInfo object.
         */
        GUIInfo GetGUIInfo() const;

        /**
         * @brief Set the GUIInfo object.
         * @date 2023-12-06
         * @param guiInfo The GUIInfo object.
         */
        void SetGUIInfo(const GUIInfo &guiInfo);
    };
}
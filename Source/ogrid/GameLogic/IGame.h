#pragma once

#include <Player/Player.h>
#include <GameLogic/GameConfiguration.h>
#include "Player/Moves.h"
#include "Player/Player.h"
#include <sstream>
#include <Grid/Grid.h>
#include <GUI/GUIInfo.h>
#include <raylib.h>

namespace OGRID
{
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
        GameState m_gameState = GameState::NotStarted;
        GameOverType m_gameOverType = GameOverType::None;
        Player *m_winner = nullptr;
        size_t m_currentTurn = 0;
        unsigned int m_totalTurns = 0;

        GameConfiguration *m_GameConfiguration = nullptr;

        IGame() = default;
        IGame(const std::vector<OGRID::PlayerNameAndPtr> &players);
        ~IGame();

    public:
        virtual bool TryMakeMove(unsigned char &row, unsigned char &col) = 0;
        virtual bool IsWinningCondition(unsigned char row, unsigned char col) = 0;
        virtual bool IsWinningCondition(char playerChar) = 0;
        virtual bool IsDrawCondition(unsigned char row, unsigned char col) = 0;
        virtual void SetupPlayers(const std::vector<OGRID::MoveType> &moveTypes) = 0;
        virtual void Initialize() = 0;
        virtual void OnGUIUpdateGrid() = 0;                  // Game specific GUI Grid stuff drawing (X and O for Tic Tac Toe for example).
        virtual void OnGUIUpdateGridHover(Vector2 cell) = 0; // On hovering over a grid spot.

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

        OGRID::GameOverType CheckGameOverState(OGRID::Grid *grid, unsigned char row, unsigned char col);

        bool IsColumnOccupied(unsigned char colToCheck, unsigned char &rowToFill) const;

        unsigned char GetTopMostPiecePositionInColumn(int col);

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

        size_t GetCurrentTurn() const;

        std::vector<std::string> GetPlayerNames() const;

        std::vector<OGRID::Player *> GetPlayerPtrs() const;

        OGRID::PlayerNameAndPtr GetPlayerPair(size_t at) const;

        std::vector<OGRID::PlayerNameAndPtr> GetPlayerPairs() const;
        void SetPlayerPairs(const std::vector<OGRID::PlayerNameAndPtr> &players);

        void SetGUIInfo(const GUIInfo &guiInfo);
        GUIInfo GetGUIInfo() const;
    };
}

template <>
struct fmt::formatter<OGRID::PlayerNameAndPtr> : fmt::formatter<std::string>
{
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const OGRID::PlayerNameAndPtr &player, FormatContext &ctx)
    {
        fmt::memory_buffer buf;

        fmt::format_to(std::back_inserter(buf), "{} [{}]", player.name, static_cast<const void *>(player.ptr));

        // Output the buffer to the formatting context and return the iterator.
        return fmt::format_to(ctx.out(), "{}", to_string(buf));
    }
};

namespace OGRID
{
    static std::string PlayerNameAndPtrVecToString(const std::vector<PlayerNameAndPtr> &players)
    {
        std::ostringstream ss;
        for (size_t i = 0; i < players.size(); ++i)
        {
            if (i > 0)
                ss << "\n";
            ss << fmt::format("{}", players[i]);
        }
        return ss.str();
    }
}

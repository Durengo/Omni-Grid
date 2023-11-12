#pragma once

#include <string>
#include <vector>

#include "fmt/format.h"

//*************************************************************
// Can't have virtual static methods, so implement them yourself
//*************************************************************

namespace OGRID
{
    // Forward declarations
    enum MoveType;
    class Player;
    struct GameConfiguration;
    class Grid;
    enum GameOverType;

    struct PlayerNameAndPtr
    {
        std::string name;
        Player *ptr;
    };

    class ITurnManager
    {
    protected:
        std::vector<OGRID::PlayerNameAndPtr> m_Players;
        size_t m_currentTurn = 0;
        unsigned int m_totalTurns = 0;

    public:
        // Constructors & Destructors
        ITurnManager(const std::vector<OGRID::PlayerNameAndPtr> &players);
        ITurnManager() = default;
        ~ITurnManager();

    protected:
        // Operators
        ITurnManager &operator++()
        {
            m_currentTurn = (m_currentTurn + 1) % m_Players.size();
            m_totalTurns++;
            return *this;
        }

        // ITurnManager operator++(int)
        //{
        //     ITurnManager temp = *this;
        //     ++(*this);
        //     return temp;
        // }

        // Private methods:
    private:
        virtual bool IsWinningCondition(OGRID::Grid *grid, unsigned char row, unsigned char col) = 0;
        virtual bool IsWinningCondition(OGRID::Grid *grid, char playerChar) = 0;
        virtual bool IsDrawCondition(OGRID::Grid *grid, unsigned char row, unsigned char col) = 0;

        // Getters & Setters
    public:
        OGRID::PlayerNameAndPtr GetCurrentPlayer() const;

        size_t GetCurrentTurn() const;

        std::vector<std::string> GetPlayerNames() const;

        std::vector<OGRID::Player *> GetPlayerPtrs() const;

        OGRID::PlayerNameAndPtr GetPlayerPair(size_t at) const;

        std::vector<OGRID::PlayerNameAndPtr> GetPlayerPairs() const;

        void SetPlayerPairs(const std::vector<OGRID::PlayerNameAndPtr> &players);

        // Public methods:
    public:
        void Reset();
        void PrintPlayerMoves() const;
        virtual void SetupPlayers(OGRID::GameConfiguration *gameConfiguration, const std::vector<OGRID::MoveType> &moveTypes, bool randomize = true) = 0;
        virtual bool MakeMove(OGRID::Grid *grid, unsigned char row, unsigned char col) = 0;
        OGRID::GameOverType CheckGameOverState(OGRID::Grid *grid, unsigned char row, unsigned char col);

        void SwapPlayerPositions();
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

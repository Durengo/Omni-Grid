//
// Created by LastWeek on 12/11/2023.
//

#pragma once

#include <string>
#include <vector>

#include "fmt/format.h"

namespace GENERICS{
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

    class ITurnManager {
    protected:
        std::vector<GENERICS::PlayerNameAndPtr> m_Players;
        size_t m_currentTurn = 0;
        unsigned int m_totalTurns = 0;

    public:
        // Constructors & Destructors
        ITurnManager(const std::vector<GENERICS::PlayerNameAndPtr> &players);
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

        //ITurnManager operator++(int)
        //{
        //    ITurnManager temp = *this;
        //    ++(*this);
        //    return temp;
        //}

        // Private methods:
    private:
        virtual bool IsWinningCondition(GENERICS::Grid *grid, unsigned char row, unsigned char col) = 0;
        virtual bool IsWinningCondition(GENERICS::Grid *grid, char playerChar) = 0;
        virtual bool IsDrawCondition(GENERICS::Grid *grid, unsigned char row, unsigned char col) = 0;

        // Getters & Setters
    public:
        GENERICS::PlayerNameAndPtr GetCurrentPlayer() const;

        size_t GetCurrentTurn() const;

        std::vector<std::string> GetPlayerNames() const;

        std::vector<GENERICS::Player *> GetPlayerPtrs() const;

        GENERICS::PlayerNameAndPtr GetPlayerPair(size_t at) const;

        std::vector<GENERICS::PlayerNameAndPtr> GetPlayerPairs() const;

        void SetPlayerPairs(const std::vector<GENERICS::PlayerNameAndPtr> &players);

        // Public methods:
    public:
        void Reset();
        void PrintPlayerMoves() const;
        virtual void SetupPlayers(GENERICS::GameConfiguration *gameConfiguration, const std::vector<GENERICS::MoveType> &moveTypes, bool randomize = true) = 0;
        virtual bool MakeMove(GENERICS::Grid *grid, unsigned char row, unsigned char col) = 0;
        GENERICS::GameOverType CheckGameOverState(GENERICS::Grid *grid, unsigned char row, unsigned char col);

        void SwapPlayerPositions();
    };
}

template <>
struct fmt::formatter<GENERICS::PlayerNameAndPtr> : fmt::formatter<std::string>
{
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const GENERICS::PlayerNameAndPtr &player, FormatContext &ctx)
    {
        fmt::memory_buffer buf;

        fmt::format_to(std::back_inserter(buf), "{} [{}]", player.name, static_cast<const void *>(player.ptr));

        // Output the buffer to the formatting context and return the iterator.
        return fmt::format_to(ctx.out(), "{}", to_string(buf));
    }
};

namespace GENERICS{
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



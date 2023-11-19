#include "Player.h"

#include <vector>
#include <map>
#include <sstream>

#include "fmt/format.h"

namespace OGRID
{
    PlayerType PlayerTypeStringToEnum(const std::string &s)
    {
        static std::map<std::string, PlayerType> stringToEnum = {{"Human", Human}, {"AI", AI}};
        return stringToEnum[s];
    }

    std::string PlayerTypeEnumToString(PlayerType playerType)
    {
        static std::map<PlayerType, std::string> enumToString = {{Human, "Human"}, {AI, "AI"}};
        return enumToString[playerType];
    }

    // Constructors & Destructors

    Player::Player(std::string playerName, PlayerType playerType, int side) : m_PlayerName(playerName), m_PlayerType(playerType), m_Side(side)
    {
    }

    Player::~Player()
    {
    }

    // Getters & Setters
    std::string Player::GetPlayerName() const
    {
        return m_PlayerName;
    }

    PlayerType Player::GetPlayerType() const
    {
        return m_PlayerType;
    }

    int Player::GetSide() const
    {
        return m_Side;
    }

    void Player::SetSide(int side)
    {
        if (side < -1)
            throw std::invalid_argument("Side must be greater than or equal to -1 (no side)");

        m_Side = side;
    }
}

// Formatting for fmt library.
template <>
struct fmt::formatter<OGRID::PlayerType> : formatter<std::string>
{
    template <typename FormatContext>
    auto format(OGRID::PlayerType p, FormatContext &ctx)
    {
        std::string name = p == OGRID::PlayerType::Human ? "Human" : "AI";
        return formatter<std::string>::format(name, ctx);
    }
};

template <>
struct fmt::formatter<OGRID::Player> : fmt::formatter<std::string>
{
    // Parses format specifications of the form '[:...]' which you can ignore.
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

    // Formats the Player using provided format specifiers.
    template <typename FormatContext>
    auto format(const OGRID::Player &player, FormatContext &ctx)
    {
        // Use a memory buffer to store the temporary output.
        fmt::memory_buffer buf;

        fmt::format_to(std::back_inserter(buf), "{} | {}", player.GetPlayerName(), player.GetPlayerType());

        // Output the buffer to the formatting context and return the iterator.
        return fmt::format_to(ctx.out(), "{}", to_string(buf));
    }
};

namespace OGRID
{
    static std::string PlayerVecToString(const std::vector<OGRID::Player *> &players)
    {
        std::ostringstream ss;
        for (size_t i = 0; i < players.size(); ++i)
        {
            if (i > 0)
                ss << "\n";
            ss << fmt::format("{}", *players[i]);
        }
        return ss.str();
    }
}
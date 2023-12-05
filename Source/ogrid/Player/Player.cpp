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

    void Player::SetPlayerName(std::string playerName)
    {
        CLI_WARN("This should not be used. It is only here for testing purposes.");

        m_PlayerName = playerName;
    }

    PlayerType Player::GetPlayerType() const
    {
        return m_PlayerType;
    }

    void Player::SetPlayerType(PlayerType playerType)
    {
        CLI_WARN("This should not be used. It is only here for testing purposes.");

        m_PlayerType = playerType;
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

    // TODO: Find a way to use fmt for this. Cannot use fmt::format as it would cause a circular dependency, because we would need to include "ogrid_fmt.h".
    std::string PlayerVecToString(const std::vector<OGRID::Player *> &players)
    {
        std::ostringstream ss;
        for (size_t i = 0; i < players.size(); ++i)
        {
            if (i > 0)
                ss << "\n";
            ss << "" + players[i]->GetPlayerName() + "|"; // + players[i]->GetPlayerType();
        }
        return ss.str();
    }
}
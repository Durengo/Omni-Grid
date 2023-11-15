#include "Player.h"

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
    Player::Player(std::string playerName, PlayerType playerType, std::shared_ptr<MoveType> moveType)
        : m_PlayerName(playerName), m_PlayerType(playerType), m_MoveType(moveType) {}

    Player::~Player() {}

    // Getters & Setters
    std::string Player::GetPlayerName() const
    {
        return m_PlayerName;
    }

    PlayerType Player::GetPlayerType() const
    {
        return m_PlayerType;
    }

    std::shared_ptr<MoveType> Player::GetPlayerMoveType() const
    {
        return m_MoveType;
    }

    void Player::SetPlayerMoveType(std::shared_ptr<MoveType> moveType)
    {
        m_MoveType = moveType;
    }
}

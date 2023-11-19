#pragma once

#include <string>

namespace OGRID
{
    // Forward declarations
    enum MoveType;

    enum PlayerType
    {
        Human = 0,
        AI = 1
    };

    PlayerType PlayerTypeStringToEnum(const std::string &s);

    std::string PlayerTypeEnumToString(PlayerType playerType);

    class Player
    {
    private:
        std::string m_PlayerName;
        PlayerType m_PlayerType;
        // The side to which the player belongs to -> -1 is no side
        int m_Side = -1;

    public:
        Player(std::string playerName = "GenericName", PlayerType playerType = PlayerType::Human, int side = -1);
        ~Player();

        // Getters & Setters
    public:
        std::string GetPlayerName() const;
        PlayerType GetPlayerType() const;

        int GetSide() const;
        void SetSide(int side);
    };

    std::string PlayerVecToString(const std::vector<Player *> &players);
}
#pragma once

#include <string>

/**
 * @file Player.h
 * @brief Contains the Player class
 * @date 2023-12-06
 */
namespace OGRID
{
    // Forward declarations
    enum MoveType;

    /**
     * @brief The type of the player.
     * @details The type of the player, either Human or AI. At the moment, the AI is not implemented.
     * @date 2023-12-06
     */
    enum PlayerType
    {
        Human = 0,
        AI = 1
    };

    /**
     * @brief Converts a string to a PlayerType.
     * @details Converts a string to a PlayerType. If the string is not a valid PlayerType, it returns PlayerType::Human.
     * @date 2023-12-06
     * @param s The string to convert.
     * @return The PlayerType corresponding to the string.
     */
    PlayerType PlayerTypeStringToEnum(const std::string &s);

    /**
     * @brief Converts a PlayerType to a string.
     * @details Converts a PlayerType to a string. If the PlayerType is not valid, it returns "Human".
     * @date 2023-12-06
     * @param playerType The PlayerType to convert.
     * @return The string corresponding to the PlayerType.
     */
    std::string PlayerTypeEnumToString(PlayerType playerType);

    /**
     * @brief The Player class. Used to represent a player.
     * @details The Player class. It contains the name of the player, the type of the player and the side to which the player belongs to.
     * @date 2023-12-06
     */
    class Player
    {
    private:
        /**
         * @brief The name of the player.
         * @details The name of the player. It is used to identify the player.
         * @date 2023-12-06
         */
        std::string m_PlayerName;

        /**
         * @brief The type of the player.
         * @details The type of the player, either Human or AI. At the moment, the AI is not implemented.
         * @date 2023-12-06
         */
        PlayerType m_PlayerType;
        // The side to which the player belongs to -> -1 is no side

        /**
         * @brief The side to which the player belongs to.
         * @details The side to which the player belongs to. -1 is no side.
         * @date 2023-12-06
         */
        int m_Side = -1;

        // Constructors & Destructors
    public:
        /**
         * @brief Construct a new Player object.
         * @details Construct a new Player object with the given name, type and side.
         * @date 2023-12-06
         * @param playerName The name of the player.
         * @param playerType The type of the player.
         * @param side The side to which the player belongs to. -1 is no side.
         */
        Player(std::string playerName = "GenericName", PlayerType playerType = PlayerType::Human, int side = -1);

        /**
         * @brief Destroy the Player object.
         * @details Destroy the Player object.
         * @date 2023-12-06
         */
        ~Player();

        // Getters & Setters
    public:
        /**
         * @brief Get the name of the player.
         * @details Get the name of the player.
         * @date 2023-12-06
         * @return The name of the player.
         */
        std::string GetPlayerName() const;

        /**
         * @brief Set the name of the player.
         * @details Set the name of the player.
         * @date 2023-12-06
         * @param playerName The name of the player.
         */
        void SetPlayerName(std::string playerName);

        /**
         * @brief Get the type of the player.
         * @details Get the type of the player.
         * @date 2023-12-06
         * @return The type of the player.
         */
        PlayerType GetPlayerType() const;

        /**
         * @brief Set the type of the player.
         * @details Set the type of the player.
         * @date 2023-12-06
         * @param playerType The type of the player.
         */
        void SetPlayerType(PlayerType playerType);

        /**
         * @brief Get the side to which the player belongs to.
         * @details Get the side to which the player belongs to.
         * @date 2023-12-06
         * @return The side to which the player belongs to.
         */
        int GetSide() const;

        /**
         * @brief Set the side to which the player belongs to.
         * @details Set the side to which the player belongs to.
         * @date 2023-12-06
         * @param side The side to which the player belongs to.
         */
        void SetSide(int side);
    };

    /**
     * @brief Converts a Vector of Players to a string.
     * @date 2023-12-06
     * @param player The Vector of Player to convert.
     * @return The string corresponding to the Vector of Players.
     */
    std::string PlayerVecToString(const std::vector<Player *> &players);
}
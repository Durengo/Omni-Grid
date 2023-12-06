#pragma once

#include <string>
#include <vector>

#include "Grid/Grid.h"
#include "Player/Player.h"

/**
 * @file GameConfiguration.h
 * @brief Contains the GameConfiguration class
 * @date 2023-12-06
 */

namespace OGRID
{
    // Forward declarations
    // class ConfigurationBuilder;
    // class ITurnManager;
    // class Player;

    /**
     * @brief Pair of player name and pointer.
     * @details Used to store the player name and pointer in the GameConfiguration class.
     * @date 2023-12-06
     */
    struct PlayerNameAndPtr
    {
        /**
         * @brief The name of the player.
         * @details The name of the player. It is used to identify the player.
         * @date 2023-12-06
         */
        std::string name;

        /**
         * @brief The pointer to the player.
         * @details The pointer to the player. It is used to access the player.
         * @date 2023-12-06
         */
        Player *ptr;
    };

    /**
     * @brief The GameConfiguration class. Used to represent a game configuration.
     * @details The GameConfiguration class. It contains the name of the game, the description of the game, the grid of the game, the maximum number of players and the players of the game.
     * @date 2023-12-06
     */
    struct GameConfiguration
    {
        /**
         * @brief The name of the game.
         * @details The name of the game. It is used to identify the game.
         * @date 2023-12-06
         */
        std::string gameName;

        /**
         * @brief The description of the game.
         * @details The description of the game. It is used to describe the game.
         * @date 2023-12-06
         */
        std::string gameDescription;

        /**
         * @brief The grid of the game.
         * @details The grid of the game. It is used to represent the game board.
         * @date 2023-12-06
         */
        Grid *grid = nullptr;

        /**
         * @brief The maximum number of players.
         * @details The maximum number of players. It is used to limit the number of players.
         * @date 2023-12-06
         */
        size_t maxPlayers = 0;

        /**
         * @brief The players of the game.
         * @details The players of the game. It is used to represent the players.
         * @date 2023-12-06
         */
        std::vector<Player *> players;

        /**
         * @brief The player pairs of the game.
         * @details The player pairs of the game. It is used to represent the player pairs.
         * @date 2023-12-06
         */
        std::vector<PlayerNameAndPtr> playerPairs;
    };

    /**
     * @brief The ConfigurationBuilder interface.
     * @details It is used to build a GameConfiguration object.
     * @date 2023-12-06
     * @see GameConfiguration
     */
    // Builder Interface
    struct ConfigurationBuilder
    {
        /**
         * @brief Destroy the ConfigurationBuilder object.
         * @date 2023-12-06
         * @see GameConfiguration
         * @see GameConfigurationBuilder
         */
        virtual ~ConfigurationBuilder() = default;

        /**
         * @brief Set the name of the game.
         * @date 2023-12-06
         * @param gameName The name of the game.
         * @return The ConfigurationBuilder object.
         * @see GameConfiguration
         */
        virtual ConfigurationBuilder &setGameName(const std::string &gameName) = 0;

        /**
         * @brief Set the description of the game.
         * @date 2023-12-06
         * @param gameDescription The description of the game.
         * @return The ConfigurationBuilder object.
         * @see GameConfiguration
         */
        virtual ConfigurationBuilder &setGameDescription(const std::string &gameDescription) = 0;

        /**
         * @brief Set the grid of the game.
         * @date 2023-12-06
         * @param rows The number of rows of the grid.
         * @param cols The number of columns of the grid.
         * @param defaultPiece The default piece of the grid.
         * @return The ConfigurationBuilder object.
         * @see GameConfiguration
         */
        virtual ConfigurationBuilder &setGrid(unsigned char rows, unsigned char cols, Piece *defaultPiece = nullptr) = 0;

        /**
         * @brief Set the maximum number of players.
         * @date 2023-12-06
         * @param maxPlayers The maximum number of players.
         * @return The ConfigurationBuilder object.
         * @see GameConfiguration
         */
        virtual ConfigurationBuilder &setMaxPlayers(size_t maxPlayers) = 0;

        /**
         * @brief Add a player to the game.
         * @date 2023-12-06
         * @param player The player to be added.
         * @return The ConfigurationBuilder object.
         * @see GameConfiguration
         */
        virtual ConfigurationBuilder &addPlayer(Player *player) = 0;

        /**
         * @brief Build the GameConfiguration object.
         * @date 2023-12-06
         * @return The GameConfiguration object.
         * @see GameConfiguration
         */
        virtual GameConfiguration *build() = 0;
    };

    /**
     * @brief The GameConfigurationBuilder class. Used to build a GameConfiguration object.
     * @details It is used to build a GameConfiguration object.
     * @date 2023-12-06
     * @see GameConfiguration
     * @see ConfigurationBuilder
     */
    // Concrete Builder
    class GameConfigurationBuilder : public ConfigurationBuilder
    {
    private:
        /**
         * @brief The GameConfiguration object.
         * @details The GameConfiguration object. It is used to store the GameConfiguration object.
         * @date 2023-12-06
         */
        GameConfiguration m_GameConfiguration;

    public:
        /**
         * @brief Construct a new GameConfigurationBuilder object.
         * @date 2023-12-06
         */
        GameConfigurationBuilder() = default;

        /**
         * @brief Destroy the GameConfigurationBuilder object.
         * @date 2023-12-06
         */
        ~GameConfigurationBuilder() override = default;

        /**
         * @brief Set the name of the game.
         * @date 2023-12-06
         * @param gameName The name of the game.
         * @return The GameConfigurationBuilder object.
         */
        ConfigurationBuilder &setGameName(const std::string &gameName) override;

        /**
         * @brief Set the description of the game.
         * @date 2023-12-06
         * @param gameDescription The description of the game.
         * @return The GameConfigurationBuilder object.
         */
        ConfigurationBuilder &setGameDescription(const std::string &gameDescription) override;

        /**
         * @brief Set the grid of the game.
         * @date 2023-12-06
         * @param rows The number of rows of the grid.
         * @param cols The number of columns of the grid.
         * @param defaultPiece The default piece of the grid.
         * @return The GameConfigurationBuilder object.
         */
        ConfigurationBuilder &setGrid(unsigned char rows, unsigned char cols, Piece *defaultPiece = nullptr) override;

        /**
         * @brief Set the maximum number of players.
         * @date 2023-12-06
         * @param maxPlayers The maximum number of players.
         * @return The GameConfigurationBuilder object.
         */
        ConfigurationBuilder &setMaxPlayers(size_t maxPlayers) override;

        /**
         * @brief Add a player to the game.
         * @date 2023-12-06
         * @param player The player to be added.
         * @return The GameConfigurationBuilder object.
         */
        ConfigurationBuilder &addPlayer(Player *player) override;

        /**
         * @brief Build the GameConfiguration object.
         * @date 2023-12-06
         * @return The GameConfiguration object.
         */
        GameConfiguration *build() override;
    };

    std::string PlayerNameAndPtrVecToString(const std::vector<PlayerNameAndPtr> &players);
}

// namespace OGRID
// {
//     static std::string PlayerNameAndPtrVecToString(const std::vector<PlayerNameAndPtr> &players)
//     {
//         std::ostringstream ss;
//         for (size_t i = 0; i < players.size(); ++i)
//         {
//             if (i > 0)
//                 ss << "\n";
//             ss << fmt::format("{}", players[i]);
//         }
//         return ss.str();
//     }
// }
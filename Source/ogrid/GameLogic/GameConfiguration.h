#pragma once

#include <string>
#include <vector>

#include "Grid/Grid.h"

namespace OGRID
{
    // Forward declarations
    class ConfigurationBuilder;
    class ITurnManager;
    class Player;

    struct PlayerNameAndPtr
    {
        std::string name;
        Player *ptr;
    };

    struct GameConfiguration
    {
        std::string gameName;
        std::string gameDescription;
        Grid *grid = nullptr;
        size_t maxPlayers = 0;
        std::vector<Player *> players;
        std::vector<PlayerNameAndPtr> playerPairs;
    };

    // Builder Interface
    struct ConfigurationBuilder
    {
        virtual ~ConfigurationBuilder() = default;
        virtual ConfigurationBuilder &setGameName(const std::string &gameName) = 0;
        virtual ConfigurationBuilder &setGameDescription(const std::string &gameDescription) = 0;
        virtual ConfigurationBuilder &setGrid(unsigned char rows, unsigned char cols, Piece *defaultPiece) = 0;
        virtual ConfigurationBuilder &setMaxPlayers(size_t maxPlayers) = 0;
        virtual ConfigurationBuilder &addPlayer(Player *player) = 0;
        virtual GameConfiguration *build() = 0;
    };

    // Concrete Builder
    class GameConfigurationBuilder : public ConfigurationBuilder
    {
    private:
        GameConfiguration m_GameConfiguration;

    public:
        GameConfigurationBuilder() = default;
        ~GameConfigurationBuilder() override = default;

        ConfigurationBuilder &setGameName(const std::string &gameName) override;
        ConfigurationBuilder &setGameDescription(const std::string &gameDescription) override;
        ConfigurationBuilder &setGrid(unsigned char rows, unsigned char cols, Piece *defaultPiece = nullptr) override;
        ConfigurationBuilder &setMaxPlayers(size_t maxPlayers) override;
        ConfigurationBuilder &addPlayer(Player *player) override;
        GameConfiguration *build() override;
    };
}



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
#pragma once

#include <string>
#include <vector>

namespace OGRID
{
    // Forward declarations
    class ConfigurationBuilder;
    class ITurnManager;
    class Player;
    class Grid;

    struct GameConfiguration
    {
        std::string gameName;
        std::string gameDescription;
        Grid *grid = nullptr;
        size_t maxPlayers = 0;
        std::vector<Player *> players;

        ITurnManager *turnManager = nullptr;
    };

    // Builder Interface
    struct ConfigurationBuilder
    {
        virtual ~ConfigurationBuilder() = default;
        virtual ConfigurationBuilder &setGameName(const std::string &gameName) = 0;
        virtual ConfigurationBuilder &setGameDescription(const std::string &gameDescription) = 0;
        virtual ConfigurationBuilder &setGrid(unsigned char rows, unsigned char cols, char initialChar = '.') = 0;
        virtual ConfigurationBuilder &setMaxPlayers(size_t maxPlayers) = 0;
        virtual ConfigurationBuilder &addPlayer(Player *player) = 0;
        virtual GameConfiguration *build(ITurnManager *turnManager) = 0;
    };

    // Concrete Builder
    class GameConfigurationBuilder : public ConfigurationBuilder
    {
    private:
        GameConfiguration m_GameConfiguration;

    public:
        GameConfigurationBuilder() = default;
        ~GameConfigurationBuilder() = default;

        ConfigurationBuilder &setGameName(const std::string &gameName) override;
        ConfigurationBuilder &setGameDescription(const std::string &gameDescription) override;
        ConfigurationBuilder &setGrid(unsigned char rows, unsigned char cols, char initialChar) override;
        ConfigurationBuilder &setMaxPlayers(size_t maxPlayers) override;
        ConfigurationBuilder &addPlayer(Player *player) override;
        GameConfiguration *build(ITurnManager *turnManager) override;
    };
}
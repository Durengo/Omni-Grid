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
        virtual ConfigurationBuilder &setGrid(unsigned char rows, unsigned char cols, char initialChar = '.') = 0;
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
        ConfigurationBuilder &setGrid(unsigned char rows, unsigned char cols, char initialChar) override;
        ConfigurationBuilder &setMaxPlayers(size_t maxPlayers) override;
        ConfigurationBuilder &addPlayer(Player *player) override;
        GameConfiguration *build() override;
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
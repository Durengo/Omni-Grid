#include "GameConfiguration.h"

#include "fmt/format.h"

#include <durlib.h>

// #include "Grid/Grid.h"
// #include "GameLogicInterface/IGame.h"

namespace OGRID
{
    ConfigurationBuilder &GameConfigurationBuilder::setGameName(const std::string &gameName)
    {
        m_GameConfiguration.gameName = gameName;
        return *this;
    }

    ConfigurationBuilder &GameConfigurationBuilder::setGameDescription(const std::string &gameDescription)
    {
        m_GameConfiguration.gameDescription = gameDescription;
        return *this;
    }

    ConfigurationBuilder &GameConfigurationBuilder::setGrid(unsigned char rows, unsigned char cols, Piece *defaultPiece)
    {
        m_GameConfiguration.grid = new Grid(rows, cols, defaultPiece);
        return *this;
    }

    ConfigurationBuilder &GameConfigurationBuilder::setMaxPlayers(size_t maxPlayers)
    {
        m_GameConfiguration.maxPlayers = maxPlayers;
        return *this;
    }

    ConfigurationBuilder &GameConfigurationBuilder::addPlayer(Player *player)
    {
        m_GameConfiguration.players.push_back(player);
        return *this;
    }

    GameConfiguration *GameConfigurationBuilder::build()
    {
        // We should make sure all the values are not null.
        if (m_GameConfiguration.gameName.empty())
            throw std::runtime_error("Game name cannot be empty.");
        CLI_INFO("Game Name: {0}", m_GameConfiguration.gameName);

        if (m_GameConfiguration.gameDescription.empty())
            throw std::runtime_error("Game description cannot be empty.");
        CLI_INFO("Game Description: {0}", m_GameConfiguration.gameDescription);

        if (m_GameConfiguration.grid == nullptr)
            throw std::runtime_error("Grid cannot be null.");
        CLI_INFO("Grid: {0}", m_GameConfiguration.grid->GetGridSize());

        if (m_GameConfiguration.maxPlayers == 0)
            throw std::runtime_error("Max players cannot be 0.");

        CLI_INFO("Player amount: {0}", m_GameConfiguration.players.size());
        CLI_ASSERT(m_GameConfiguration.players.size() > 1, "TicTacToeTurnManager cannot be initialized due to lack of players.");
        CLI_INFO("Players:\n{0}", PlayerVecToString(m_GameConfiguration.players));
        CLI_ASSERT(m_GameConfiguration.players.size() <= m_GameConfiguration.maxPlayers, "Player amount exceeds max player amount.");

        std::vector<PlayerNameAndPtr> playerPairs;
        playerPairs.reserve(m_GameConfiguration.players.size());
        for (auto player : m_GameConfiguration.players)
        {
            playerPairs.push_back({player->GetPlayerName(), player});
        }
        m_GameConfiguration.playerPairs = playerPairs;
        // m_GameConfiguration.turnManager = turnManager;
        // m_GameConfiguration.turnManager->SetPlayerPairs(playerPairs);
        // CLI_INFO("TicTacToeTurnManager initialized.");
        // CLI_INFO("Player Pairs:\n{0}", OGRID::PlayerNameAndPtrVecToString(m_GameConfiguration.turnManager->GetPlayerPairs()));

        return new GameConfiguration(m_GameConfiguration);
    }

    // std::string PlayerNameAndPtrVecToString(const std::vector<PlayerNameAndPtr> &players)
    // {
    //     std::ostringstream ss;
    //     for (size_t i = 0; i < players.size(); ++i)
    //     {
    //         if (i > 0)
    //             ss << "\n";
    //         ss << fmt::format("{}", players[i]);
    //     }
    //     return ss.str();
    // }
}

/**
 * @brief This is used to format a PlayerType enum into a string using fmt.
 * @details This should be used like this: fmt::format("{}", playerType);
 * The reason this is here and not in ogrid_fmt.h is because it needs to be declared before the Player class.
 * @date 2023-12-06
 * @todo Try to move this to ogrid_fmt.h at some point.
*/
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

std::string OGRID::PlayerNameAndPtrVecToString(const std::vector<OGRID::PlayerNameAndPtr> &players)
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

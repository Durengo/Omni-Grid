#include "IGame.h"

#include <durlib.h>

#include "ogrid_fmt.h"

#include "Grid/Grid.h"
#include "Player/Player.h"
#include "GameLogicImplementation/GameConfiguration.h"

namespace OGRID
{
    IGame::IGame(IGameState *gameStateStrategy, const std::vector<OGRID::PlayerNameAndPtr> &players)
    {
        m_GameConfiguration->playerPairs = players;
        m_currentGameState = new GameStateChecker(gameStateStrategy);
    }

    IGame::~IGame()
    {
        for (auto &playerPair : m_GameConfiguration->playerPairs)
        {
            playerPair.ptr = nullptr;
            delete playerPair.ptr;
        }
    }

    void OGRID::IGame::SwapPlayerPositions()
    {
        if (m_GameConfiguration->playerPairs.size() == 2)
        {
            std::swap(m_GameConfiguration->playerPairs[0], m_GameConfiguration->playerPairs[1]);
        }
        else
        {
            throw std::runtime_error("Cannot swap player positions if there are more than 2 players.");
        }
    }

    void OGRID::IGame::ResetGrid()
    {
        CLI_ASSERT(m_GameConfiguration->grid, "Grid not initialized.");

        m_GameConfiguration->grid->ResetGrid();
    }

    void IGame::ResetPlayers()
    {
        // HARDCODED
        // std::vector<OGRID::MoveType> moveTypes;
        // moveTypes.push_back(OGRID::MoveType::X);
        // moveTypes.push_back(OGRID::MoveType::O);
        // // HARDCODED

        SetupPlayers();
        PrintPlayerMoves();
    }

    void IGame::PrintPlayersTurnOrder() const
    {
        std::string players;
        auto playerPairs = GetPlayerPairs();
        for (size_t i = 0; i < playerPairs.size(); ++i)
        {
            players +=
                playerPairs[i].ptr->GetPlayerName() + "\t| " +
                OGRID::PlayerTypeEnumToString(playerPairs[i].ptr->GetPlayerType()) + "\t| " +
                std::to_string(playerPairs[i].ptr->GetSide());
            // Add the newline character if it's not the last player
            if (i < playerPairs.size() - 1)
            {
                players += " |\n";
            }
            else
            {
                // Do not add newline at the end
                players += " |";
            }
        }
        CLI_TRACE("Player Turn Order:\n{}", players);
    }

    void IGame::SetupGame()
    {
        m_gameState = OGRID::GameState::NotStarted;
        m_gameOverType = OGRID::GameOverType::None;
        ResetGame();
    }

    void IGame::ResetGame()
    {
        m_gameState = OGRID::GameState::NotStarted;
        m_gameOverType = OGRID::GameOverType::None;

        CLI_INFO("Setting up game: {}", m_GameConfiguration->gameName);
        CLI_TRACE("Game description: {}", m_GameConfiguration->gameDescription);

        CLI_TRACE("Resetting grid.");
        ResetGrid();

        CLI_TRACE("Resetting turns.");
        Reset();

        CLI_TRACE("Setting up players.");
        ResetPlayers();

        m_winner = nullptr;
    }

    void IGame::StartGame()
    {
        CLI_INFO("Starting game: {}", m_GameConfiguration->gameName);
        CLI_TRACE("Game description: {}", m_GameConfiguration->gameDescription);

        m_gameState = OGRID::GameState::InProgress;

        CLI_TRACE("Grid: {}", *m_GameConfiguration->grid);
        PrintPlayersTurnOrder();
    }

    void IGame::MakeMove(unsigned char row, unsigned char col)
    {
        if (TryMakeMove(row, col) && m_gameState == OGRID::GameState::InProgress)
        {
            CLI_TRACE("\n{}", m_GameConfiguration->grid->GetGridAsString());
            switch (CheckGameOverState(m_GameConfiguration->grid, row, col))
            {
            case OGRID::GameOverType::None:
                m_gameState = OGRID::GameState::InProgress;
                // i_instance->m_GameConfiguration->turnManager++;
                break;
            case OGRID::GameOverType::Win:
                m_gameState = OGRID::GameState::GameOver;
                m_gameOverType = OGRID::GameOverType::Win;
                m_winner = GetCurrentPlayer().ptr;
                PrintPlayersTurnOrder();
                break;
            case OGRID::GameOverType::Draw:
                m_gameState = OGRID::GameState::GameOver;
                m_gameOverType = OGRID::GameOverType::Draw;
                PrintPlayersTurnOrder();
                break;
            default:
                CLI_ERROR("Invalid GameOverType.");
                break;
            }
        }
        else
        {
            throw std::runtime_error("Invalid move.");
        }
    }

    OGRID::GameOverType IGame::CheckGameOverState(OGRID::Grid *grid, unsigned char row, unsigned char col)
    {
        OGRID::PlayerNameAndPtr currentPlayer = GetCurrentPlayer();
        // PlayerNameAndPtr previousPlayer = GetPlayerPair((GetCurrentTurn() - 1) % m_GameConfiguration->playerPairs.size());

        if (IsWinningCondition())
        {
            CLI_INFO("Player {0} won the game!", currentPlayer.name);
            // m_gameOverType = GameOverType::Win;
            // m_winner = m_currentPlayer;
            // m_gameState = GameState::GameOver;
            return OGRID::GameOverType::Win;
        }
        if (IsDrawCondition())
        {
            CLI_INFO("The game ended in a draw!");
            // m_gameOverType = GameOverType::Draw;
            // m_gameState = GameState::GameOver;
            return OGRID::GameOverType::Draw;
        }
        CLI_TRACE("Player {0} finished his move.", currentPlayer.name);
        m_currentTurn = (m_currentTurn + 1) % m_GameConfiguration->players.size();
        m_totalTurns++;
        CLI_TRACE("Player {0} is now playing.", GetCurrentPlayer().name);
        m_currentPlayer = GetCurrentPlayer().ptr;
        return OGRID::GameOverType::None;
    }

    GameState IGame::GetGameState() const
    {
        return m_gameState;
    }

    void IGame::SetGameState(GameState gameState)
    {
        m_gameState = gameState;
    }

    GameOverType IGame::GetGameOverType() const
    {
        return m_gameOverType;
    }

    Player *IGame::GetWinner() const
    {
        return m_winner;
    }

    GameConfiguration *IGame::GetGameConfiguration() const
    {
        DEBUG_ASSERT(m_GameConfiguration, "GameConfiguration not initialized.");

        return m_GameConfiguration;
    }

    void IGame::SetGameConfiguration(GameConfiguration *gameConfiguration)
    {
        m_GameConfiguration = gameConfiguration;
    }

    std::string IGame::GetGameName() const
    {
        CLI_ASSERT(!m_GameConfiguration->gameName.empty(), "Name not initialized.");

        return m_GameConfiguration->gameName;
    }

    Grid *IGame::GetGrid() const
    {
        CLI_ASSERT(m_GameConfiguration->grid, "Grid not initialized.");

        return m_GameConfiguration->grid;
    }

    std::vector<Player *> IGame::GetPlayers() const
    {
        return m_GameConfiguration->players;
    }

    void IGame::SetRandomizeTurnOrder(bool randomize)
    {
        m_randomizeTurnOrder = randomize;
    }

    OGRID::PlayerNameAndPtr IGame::GetCurrentPlayer() const
    {
        return m_GameConfiguration->playerPairs[m_currentTurn];
    }

    size_t IGame::GetCurrentTurn() const
    {
        return m_currentTurn;
    }

    std::vector<std::string> IGame::GetPlayerNames() const
    {
        std::vector<std::string> playerNames;
        playerNames.reserve(m_GameConfiguration->playerPairs.size());
        for (const auto &playerPair : m_GameConfiguration->playerPairs)
        {
            playerNames.push_back(playerPair.name);
        }
        return playerNames;
    }

    std::vector<OGRID::Player *> IGame::GetPlayerPtrs() const
    {
        std::vector<OGRID::Player *> playerPtrs;
        playerPtrs.reserve(m_GameConfiguration->playerPairs.size());
        for (const auto &playerPair : m_GameConfiguration->playerPairs)
        {
            playerPtrs.push_back(playerPair.ptr);
        }
        return playerPtrs;
    }

    OGRID::PlayerNameAndPtr IGame::GetPlayerPair(size_t at) const
    {
        if (at < m_GameConfiguration->playerPairs.size())
        {
            return m_GameConfiguration->playerPairs[at];
        }
        else
        {
            throw std::out_of_range("Index out of range in GetPlayerPair");
        }
    }

    std::vector<OGRID::PlayerNameAndPtr> IGame::GetPlayerPairs() const
    {
        return m_GameConfiguration->playerPairs;
    }

    void IGame::SetPlayerPairs(const std::vector<OGRID::PlayerNameAndPtr> &players)
    {
        m_GameConfiguration->playerPairs = players;
    }

    void IGame::PrintPlayerMoves() const
    {
        for (const auto &playerPair : m_GameConfiguration->playerPairs)
        {
            CLI_TRACE("{0} | {1}", playerPair.name, playerPair.ptr->GetSide());
        }
    }

    void IGame::Reset()
    {
        m_currentTurn = 0;
        m_totalTurns = 0;
    }

    void IGame::SetGUIInfo(const GUIInfo &guiInfo)
    {
        m_guiInfo = guiInfo;
    }

    GUIInfo IGame::GetGUIInfo() const
    {
        return m_guiInfo;
    }

    // bool IGame::IsColumnOccupied(unsigned char colToCheck, unsigned char &rowToFill) const
    // {
    //     // Iterate through the column from bottom to top
    //     for (int row = GetGameConfiguration()->grid->GetRows() - 1; row >= 0; --row)
    //     {
    //         if (GetGameConfiguration()->grid->GetCharAt(row, colToCheck) == GetGameConfiguration()->grid->GetDefaultChar())
    //         {
    //             // Found an empty spot in the column
    //             rowToFill = static_cast<unsigned char>(row);
    //             return true;
    //         }
    //     }

    //     // Column is fully occupied
    //     return false;
    // }

    // unsigned char IGame::GetTopMostPiecePositionInColumn(int col)
    // {
    //     // Go down the column
    //     for (unsigned char row = 0; row < m_GameConfiguration->grid->GetRows(); ++row)
    //     {
    //         if (m_GameConfiguration->grid->GetCharAt(row, col) != m_GameConfiguration->grid->GetDefaultChar())
    //         {
    //             // Found the first piece
    //             return row;
    //         }
    //     }
    //     // Column is empty
    //     return static_cast<unsigned char>(m_GameConfiguration->grid->GetRows());
    // }

    // void IGame::ChangeGridSize() {
    // CLI_TRACE("Input the dimensions of the grid (3-10): ");
    // auto dimensions = static_cast<unsigned char>(DURLIB::GIBI(3, 10));
    // m_gridSize = dimensions;
    //
    // instance->i_gameLogic->GetGameConfiguration()->grid->ResetGridWithNewSize(dimensions, dimensions, '.');
    // }
}

#include "TicTacToeLogic.h"
#include "TicTacToeInstance.h"

#include <durlib.h>
#include <ogrid.h>

namespace OGRIDSandbox
{
    // Static variables

    bool TicTacToeLogic::m_randomizeTurnOrder{true};
    TicTacToeLogic *instance = TicTacToeInstance::GetInstance();

    // Constructors & Destructors
    TicTacToeLogic::TicTacToeLogic() = default;

    TicTacToeLogic::~TicTacToeLogic() = default;

    // Getters & Setters

    void TicTacToeLogic::SetRandomizeTurnOrder(bool randomize)
    {
        m_randomizeTurnOrder = randomize;
    }

    // Private methods

    void TicTacToeLogic::ResetGrid()
    {
        CLI_ASSERT(m_GameConfiguration->grid, "Grid not initialized.");

        instance->m_GameConfiguration->grid->ResetGrid();
    }

    void TicTacToeLogic::ResetPlayers()
    {
        CLI_ASSERT(instance->m_GameConfiguration->turnManager, "TicTacToeTurnManager not initialized.");

        // HARDCODED
        std::vector<OGRID::MoveType> moveTypes;
        moveTypes.push_back(OGRID::MoveType::X);
        moveTypes.push_back(OGRID::MoveType::O);
        // HARDCODED

        instance->m_GameConfiguration->turnManager->SetupPlayers(instance->m_GameConfiguration, moveTypes, m_randomizeTurnOrder);
        instance->m_GameConfiguration->turnManager->PrintPlayerMoves();
    }

    void TicTacToeLogic::PrintPlayersTurnOrder()
    {
        std::string players;
        auto playerPairs = instance->m_GameConfiguration->turnManager->GetPlayerPairs();
        for (size_t i = 0; i < playerPairs.size(); ++i)
        {
            players +=
                playerPairs[i].ptr->GetPlayerName() + "\t| " +
                OGRID::PlayerTypeEnumToString(playerPairs[i].ptr->GetPlayerType()) + "\t| " +
                OGRID::MoveTypeEnumToString(playerPairs[i].ptr->GetPlayerMoveType());
            // Add the newline character if it's not the last player
            if (i < playerPairs.size() - 1)
            {
                players += " |\n";
            }
            else
            {
                players += " |"; // Do not add newline at the end
            }
        }
        CLI_TRACE("Player Turn Order:\n{}", players);
    }

    // Public methods

    void TicTacToeLogic::SetupGame()
    {
        m_gameState = OGRID::GameState::NotStarted;
        m_gameOverType = OGRID::GameOverType::None;
        ResetGame();
    }

    void TicTacToeLogic::ResetGame()
    {
        if (TicTacToeInstance::CheckInit())
        {
            m_gameState = OGRID::GameState::NotStarted;
            m_gameOverType = OGRID::GameOverType::None;

            CLI_INFO("Setting up game: {}", instance->m_GameConfiguration->gameName);
            CLI_TRACE("Game description: {}", instance->m_GameConfiguration->gameDescription);

            CLI_TRACE("Resetting grid.");
            instance->ResetGrid();

            CLI_TRACE("Resetting turns.");
            instance->m_GameConfiguration->turnManager->Reset();

            CLI_TRACE("Setting up players.");
            instance->ResetPlayers();

            m_winner = nullptr;
        }
    }

    void TicTacToeLogic::StartGame()
    {
        if (TicTacToeInstance::CheckInit())
        {
            CLI_INFO("Starting game: {}", instance->m_GameConfiguration->gameName);
            CLI_TRACE("Game description: {}", instance->m_GameConfiguration->gameDescription);

            m_gameState = OGRID::GameState::InProgress;

            CLI_TRACE("Grid: {}", *instance->m_GameConfiguration->grid);
            instance->PrintPlayersTurnOrder();
            // i_instance->m_GameConfiguration->turnManager->StartGame();
        }
    }

    void TicTacToeLogic::MakeMove(unsigned char row, unsigned char col)
    {
        if (TicTacToeInstance::CheckInit())
        {
            if (instance->m_GameConfiguration->turnManager->MakeMove(instance->m_GameConfiguration->grid, row, col) && m_gameState == OGRID::GameState::InProgress)
            {
                CLI_TRACE("{}", *instance->m_GameConfiguration->grid);
                switch (instance->m_GameConfiguration->turnManager->CheckGameOverState(instance->m_GameConfiguration->grid, row, col))
                {
                case OGRID::GameOverType::None:
                    m_gameState = OGRID::GameState::InProgress;
                    // i_instance->m_GameConfiguration->turnManager++;
                    break;
                case OGRID::GameOverType::Win:
                    m_gameState = OGRID::GameState::GameOver;
                    m_gameOverType = OGRID::GameOverType::Win;
                    m_winner = instance->m_GameConfiguration->turnManager->GetCurrentPlayer().ptr;
                    instance->PrintPlayersTurnOrder();
                    break;
                case OGRID::GameOverType::Draw:
                    m_gameState = OGRID::GameState::GameOver;
                    m_gameOverType = OGRID::GameOverType::Draw;
                    instance->PrintPlayersTurnOrder();
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
    }

    void TicTacToeLogic::SwapPlayerPositions()
    {
        if (TicTacToeInstance::CheckInit())
        {
            std::swap(instance->m_GameConfiguration->players[0], instance->m_GameConfiguration->players[1]);
            instance->m_GameConfiguration->turnManager->SwapPlayerPositions();
        }
    }
}
#include "ConnectFourLogic.h"
#include "ConnectFourInstance.h"

#include <durlib.h>
#include <ogrid.h>

namespace OGRIDSandbox{
    bool ConnectFourLogic::m_randomizeTurnOrder{true};
    ConnectFourLogic *instance = ConnectFourInstance::GetInstance();

    // Constructors & Destructors
    ConnectFourLogic::ConnectFourLogic() = default;

    ConnectFourLogic::~ConnectFourLogic() = default;

    void ConnectFourLogic::SetRandomizeTurnOrder(bool randomize)
    {
        m_randomizeTurnOrder = randomize;
    }

    void ConnectFourLogic::ResetGrid() {
        CLI_ASSERT(m_GameConfiguration->grid, "Grid not initialized.");

        instance->m_GameConfiguration->grid->ResetGrid();
    }

    void ConnectFourLogic::ResetPlayers() {
        CLI_ASSERT(instance->m_GameConfiguration->turnManager, "ConnectFourManager not initialized.");

        // HARDCODED
        std::vector<OGRID::MoveType> moveTypes; //********************************************
        moveTypes.push_back(OGRID::MoveType::X); //USING X AND O FOR NOW SINCE IT JUST WORKS™
        moveTypes.push_back(OGRID::MoveType::O); //*******************************************
        // HARDCODED

        instance->m_GameConfiguration->turnManager->SetupPlayers(instance->m_GameConfiguration, moveTypes, m_randomizeTurnOrder);
        instance->m_GameConfiguration->turnManager->PrintPlayerMoves();
    }

    void ConnectFourLogic::PrintPlayersTurnOrder() {
        std::string players;
        auto playerPairs = instance->m_GameConfiguration->turnManager->GetPlayerPairs();
        for (size_t i = 0; i < playerPairs.size(); ++i)
        {
            std::string move = OGRID::MoveTypeEnumToString(playerPairs[i].ptr->GetPlayerMoveType());
            if (move == "X")                                                                        //  **************
            {                                                                                       //      USING
                move = "RED";                                                                       //     X AND O
            }                                                                                       //     FOR NOW
            else                                                                                    //
            {                                                                                       //     SUE ME
                move = "BLACK";                                                                     //
            }                                                                                       //  **************
            players +=
                    playerPairs[i].ptr->GetPlayerName() + "\t| " +
                    OGRID::PlayerTypeEnumToString(playerPairs[i].ptr->GetPlayerType()) + "\t| " +
                    move;
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

    void ConnectFourLogic::SetupGame() {
        m_gameState = OGRID::GameState::NotStarted;
        m_gameOverType = OGRID::GameOverType::None;
        ResetGame();
    }

    void ConnectFourLogic::ResetGame() {
        if (ConnectFourInstance::CheckInit())
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

    void ConnectFourLogic::StartGame() {
        if (ConnectFourInstance::CheckInit())
        {
            CLI_INFO("Starting game: {}", instance->m_GameConfiguration->gameName);
            CLI_TRACE("Game description: {}", instance->m_GameConfiguration->gameDescription);

            m_gameState = OGRID::GameState::InProgress;

            CLI_TRACE("Grid: {}", *instance->m_GameConfiguration->grid);
            instance->PrintPlayersTurnOrder();
            // i_instance->m_GameConfiguration->turnManager->StartGame();
        }
    }

    void ConnectFourLogic::MakeMove(unsigned char row, unsigned char col) {
        if (ConnectFourInstance::CheckInit())
        {
            if (instance->m_GameConfiguration->turnManager->MakeMove(instance->m_GameConfiguration->grid, row, col) && m_gameState == OGRID::GameState::InProgress)
            {
                // Because of not enough generalizations, I'll have to create a method
                // that checks from the position the piece was placed, and not the position that was clicked.
                row = GetTopMostPiecePositionInColumn(col);
                if (row > m_GameConfiguration->grid->GetRows() - 1 || row < 0)
                {
                    throw std::runtime_error("GetTopMostPiecePositionInColumn returned invalid row.");
                }
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

    void ConnectFourLogic::SwapPlayerPositions() {
        if (ConnectFourInstance::CheckInit())
        {
            std::swap(instance->m_GameConfiguration->players[0], instance->m_GameConfiguration->players[1]);
            instance->m_GameConfiguration->turnManager->SwapPlayerPositions();
        }
    }

    unsigned char ConnectFourLogic::GetTopMostPiecePositionInColumn(int col) {
        // Go down the column
        for (unsigned char row = 0; row < instance->m_GameConfiguration->grid->GetRows(); ++row) {
            if (instance->m_GameConfiguration->grid->GetCharAt(row, col) != instance->m_GameConfiguration->grid->GetDefaultChar()) {
                // Found the first piece
                return row;
            }
        }

        // Column is empty
        return static_cast<unsigned char>(instance->m_GameConfiguration->grid->GetRows());
    }
}
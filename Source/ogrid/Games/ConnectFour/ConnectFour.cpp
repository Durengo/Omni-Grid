#include "ConnectFour.h"

#include <random>

#include <durlib.h>

#include "GameLogicImplementation/GameConfiguration.h"
#include "Games/ConnectFour/ConnectFourPieces.h"
#include "Games/ConnectFour/ConnectFourStateCheck.h"
#include "Player/Piece.h"
#include "Player/Player.h"
#include "User/Score.h"

namespace OGRID
{
    bool ConnectFour::TryMakeMove(unsigned char &row, unsigned char &col)
    {
        Piece *piece = nullptr;
        // Create a new piece with the current player's move type, in this case team.
        switch (m_currentPlayer->GetSide())
        {
        case -1:
            CLI_FATAL("Player side is not set.");
            break;
            // X
        case 0:
            piece = new RedPiece(m_currentPlayer);
            break;
            // O
        case 1:
            piece = new BlackPiece(m_currentPlayer);
            break;
        default:
            CLI_FATAL("Invalid player side.");
            break;
        }
        // Check if the column is occupied and find the topmost available spot
        if (m_currentGameState->IsColumnOccupied(GetGameConfiguration()->grid, col, row))
        {
            CLI_WARN("Cannot make move at column {0}, because it is fully occupied", col);
            return false;
        }

        // Set the player's move in the grid
        if (piece->isValidMove(GetGameConfiguration()->grid, 0, 0, col, row))
        {
            GetGameConfiguration()->grid->SetPieceAt(row, col, piece);
        }
        else
        {
            CLI_WARN("Invalid move.");
            return false;
        }

        // this->operator++();
        return true;
    }

    bool ConnectFour::IsWinningCondition()
    {
        switch (m_currentGameState->CheckWin(GetGameConfiguration()->grid))
        {
        case -1:
            return false;
        default:
            m_winner = m_currentPlayer;

            if (m_User != nullptr)
            {
                if (m_winner == m_User->GetPlayer())
                {
                    m_User->GetScore()->AddWin();
                }
                else
                {
                    m_User->GetScore()->AddLoss();
                }
            }

            return true;
        }
    }

    bool ConnectFour::IsDrawCondition()
    {
        if (m_currentGameState->IsDraw(GetGameConfiguration()->grid))
        {
            return true;
        }
        return false;
    }

    void ConnectFour::SetupPlayers()
    {
        size_t allowedPlayers = GetGameConfiguration()->maxPlayers;
        std::vector<int> totalValidSides = {0, 1};

        // CLI_ASSERT(GetGameConfiguration()->playerPairs.size() > allowedPlayers, "Player amount exceeds max player amount.");

        if (m_randomizeTurnOrder)
        {
            std::vector<int> shuffledMoveTypes = totalValidSides;
            std::random_device rd;
            auto rng = std::default_random_engine{rd()};
            std::shuffle(shuffledMoveTypes.begin(), shuffledMoveTypes.end(), rng);

            for (int i = 0; i < GetGameConfiguration()->playerPairs.size(); i++)
            {
                GetGameConfiguration()->playerPairs[i].ptr->SetSide(shuffledMoveTypes[i % shuffledMoveTypes.size()]);
            }

            std::stable_sort(GetGameConfiguration()->playerPairs.begin(), GetGameConfiguration()->playerPairs.end(),
                             [](const OGRID::PlayerNameAndPtr &a, const OGRID::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetSide() == 0;
                             });
        }
        else
        {
            for (int i = 0; i < GetGameConfiguration()->playerPairs.size(); i++)
            {
                GetGameConfiguration()->playerPairs[i].ptr->SetSide(totalValidSides[i % totalValidSides.size()]);
            }

            std::stable_sort(GetGameConfiguration()->playerPairs.begin(), GetGameConfiguration()->playerPairs.end(),
                             [](const OGRID::PlayerNameAndPtr &a, const OGRID::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetSide() == 0;
                             });
        }

        m_currentPlayer = GetGameConfiguration()->playerPairs[0].ptr;
    }

    void ConnectFour::Initialize(OGRID::User *user)
    {
        m_User = user;

        m_currentGameState = new GameStateChecker(new ConnectFourStateCheck());

        m_guiInfo = *new GUIInfo();
        m_guiInfo.windowName = "ConnectFour";
        m_guiInfo.width = 800;
        m_guiInfo.height = 600;
        m_guiInfo.targetFPS = 60;
        m_guiInfo.lineThickness = 2.5f;
        m_guiInfo.margin = 30.0f;

        auto *p1 = new OGRID::Player(m_User->GetUserName(), OGRID::Human);
        m_User->SetPlayer(p1);
        auto *p2 = new OGRID::Player("Player2", OGRID::Human);

        int choice = 0;
        while (choice == 0)
        {
            CLI_TRACE("\n1. Start as RED\n2. Start as BLACK\n3. Random");
            choice = DURLIB::GIBI(1, 3);
        }

        // I WILL CONTINUE TO USE X AND O https://i.imgur.com/of0oR9s.mp4
        if (choice == 1)
        {
            SetRandomizeTurnOrder(false);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                     .setGameName("ConnectFour")
                                     .setGameDescription("ConnectFour Game")
                                     .setGrid(6, 7)
                                     .setMaxPlayers(2)
                                     .addPlayer(p1)
                                     .addPlayer(p2)
                                     .build());
        }
        else if (choice == 2)
        {
            SetRandomizeTurnOrder(false);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                     .setGameName("ConnectFour")
                                     .setGameDescription("ConnectFour Game")
                                     .setGrid(6, 7)
                                     .setMaxPlayers(2)
                                     .addPlayer(p2)
                                     .addPlayer(p1)
                                     .build());
        }
        else if (choice == 3)
        {
            SetRandomizeTurnOrder(true);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                     .setGameName("ConnectFour")
                                     .setGameDescription("ConnectFour Game")
                                     .setGrid(6, 7)
                                     .setMaxPlayers(2)
                                     .addPlayer(p1)
                                     .addPlayer(p2)
                                     .build());
        }
    }

    void ConnectFour::OnGUIUpdateGrid()
    {
        for (int row = 0; row < GetGameConfiguration()->grid->GetRows(); row++)
        {
            for (int col = 0; col < GetGameConfiguration()->grid->GetCols(); col++)
            {
                Piece *piece = GetGrid()->GetPieceAt(row, col);
                if (piece == nullptr)
                {
                    continue;
                }
                if (piece->GetOwner()->GetSide() == 0)
                {
                    DrawCircle(row, col, RED, false);
                }
                else if (piece->GetOwner()->GetSide() == 1)
                {
                    DrawCircle(row, col, BLACK, false);
                }
                else
                {
                    throw std::runtime_error("Invalid cell type.");
                }
            }
        }
    }

    void ConnectFour::OnGUIUpdateGridHover(Vector2 cell)
    {
        if (cell.x != -1 && cell.y != -1)
        {
            int col = static_cast<int>(cell.x);
            int row = m_currentGameState->GetTopMostPiecePositionInColumn(GetGameConfiguration()->grid, col) - 1;

            if (row >= 0 && row < GetGrid()->GetRows())
            {
                if (GetCurrentPlayer().ptr->GetSide() == 0)
                {
                    DrawCircle(row, col, RED, true);
                }
                else if (GetCurrentPlayer().ptr->GetSide() == 1)
                {
                    DrawCircle(row, col, BLACK, true);
                }
                else
                {
                    throw std::runtime_error("Invalid player move type.");
                }
            }
        }
    }

    void ConnectFour::DrawCircle(int row, int col, Color color, bool blinking)
    {
        // Use the same margin for consistency
        float padding = m_guiInfo.margin;

        // Calculate offsets for non-square windows (same as in DrawGrid)
        float xOffset = (m_guiInfo.width - (m_guiInfo.cellSize * GetGrid()->GetCols())) / 2.0f;
        float yOffset = (m_guiInfo.height - (m_guiInfo.cellSize * GetGrid()->GetRows())) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Calculate the center of the circle
        float centerX = xOffset + (col + 0.5f) * m_guiInfo.cellSize;
        float centerY = yOffset + (row + 0.5f) * m_guiInfo.cellSize;

        // Calculate the radius of the circle based on cell size and padding
        float radius = m_guiInfo.cellSize / 2.0f;

        if (blinking)
        {
            if (alpha == 1.0f || alpha == 0.0f)
            {
                // Invert the speed
                alphaSpeed = -alphaSpeed;
            }
            alpha += alphaSpeed;
            alpha = std::clamp(alpha, 0.0f, 1.0f);
            DrawCircleV(Vector2{centerX, centerY}, radius, Fade(color, alpha));
        }
        else
        {
            DrawCircleV(Vector2{centerX, centerY}, radius, color);
        }
    }
}

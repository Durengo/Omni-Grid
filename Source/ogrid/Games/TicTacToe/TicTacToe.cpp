#include "TicTacToe.h"

#include <durlib.h>
#include <raylib.h>

#include "GameLogicImplementation/GameConfiguration.h"
#include "Games/TicTacToe/TicTacToePieces.h"
#include "Games/TicTacToe/TicTacToeStateCheck.h"
#include "Player/Piece.h"
#include "Player/Player.h"

namespace OGRID
{
    bool TicTacToe::TryMakeMove(unsigned char &row, unsigned char &col)
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
            piece = new XPiece(m_currentPlayer);
            break;
            // O
        case 1:
            piece = new OPiece(m_currentPlayer);
            break;
        default:
            CLI_FATAL("Invalid player side.");
            break;
        }

        CLI_ASSERT(piece, "Piece is null.");

        if (piece->isValidMove(GetGameConfiguration()->grid, 0, 0, row, col))
        {
            GetGameConfiguration()->grid->SetPieceAt(row, col, piece);
            return true;
        }
        return false;
    }

    bool TicTacToe::IsWinningCondition()
    {
        switch (m_currentGameState->CheckWin(GetGameConfiguration()->grid))
        {
        case -1:
            return false;
        default:
            return true;
        }
    }

    bool TicTacToe::IsDrawCondition()
    {
        return m_currentGameState->IsDraw(GetGameConfiguration()->grid);
    }

    // void TicTacToe::SetupPlayers(const std::vector<int> &totalValidSides)
    void TicTacToe::SetupPlayers()
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

            // Assuming MoveType::X is the MoveType that goes first.
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

    void TicTacToe::OnGUIUpdateGrid()
    {
        for (int i = 0; i < GetGameConfiguration()->grid->GetRows(); i++)
        {
            for (int j = 0; j < GetGameConfiguration()->grid->GetCols(); j++)
            {
                Piece *piece = GetGrid()->GetPieceAt(i, j);
                if (piece == nullptr)
                {
                    continue;
                }

                if (piece->GetOwner()->GetSide() == 0)
                {
                    DrawX(i, j);
                }
                else if (piece->GetOwner()->GetSide() == 1)
                {
                    DrawO(i, j);
                }
            }
        }
    }

    void TicTacToe::DrawX(int row, int col)
    {
        // Use the same margin for consistency
        float padding = m_guiInfo.margin;

        // Calculate offsets for non-square windows (same as in DrawGrid)
        float xOffset = (m_guiInfo.width - (m_guiInfo.cellSize * GetGrid()->GetCols())) / 2.0f;
        float yOffset = (m_guiInfo.height - (m_guiInfo.cellSize * GetGrid()->GetRows())) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Calculate the starting and ending points for the two lines of the X
        float startX = xOffset + col * m_guiInfo.cellSize + padding;
        float startY = yOffset + row * m_guiInfo.cellSize + padding;
        float endX = xOffset + (col + 1) * m_guiInfo.cellSize - padding;
        float endY = yOffset + (row + 1) * m_guiInfo.cellSize - padding;

        // Draw the first diagonal line of the X
        DrawLine(startX, startY, endX, endY, BLACK);

        // Draw the second diagonal line of the X
        DrawLine(startX, endY, endX, startY, BLACK);
    }

    void TicTacToe::DrawO(int row, int col)
    {
        // Use the same margin for consistency and to make sure 'O' is within the cell bounds
        float padding = m_guiInfo.margin;

        // Calculate offsets for non-square windows (same as in DrawGrid)
        float xOffset = (m_guiInfo.width - (m_guiInfo.cellSize * GetGrid()->GetCols())) / 2.0f;
        float yOffset = (m_guiInfo.height - (m_guiInfo.cellSize * GetGrid()->GetRows())) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Radius of 'O' should probably be a bit less than half the cell size to fit within the cell,
        // minus some padding to avoid touching the cell borders.
        float radius = (m_guiInfo.cellSize / 2) - padding;

        // Center point calculations now include the offset and padding
        float centerX = xOffset + col * m_guiInfo.cellSize + (m_guiInfo.cellSize / 2);
        float centerY = yOffset + row * m_guiInfo.cellSize + (m_guiInfo.cellSize / 2);

        DrawCircleLines(centerX, centerY, radius, BLACK);
    }

    void TicTacToe::Initialize()
    {
        m_currentGameState = new GameStateChecker(new TicTacToeStateCheck());

        m_guiInfo = *new GUIInfo();
        m_guiInfo.windowName = "TicTacToe";
        m_guiInfo.width = 800;
        m_guiInfo.height = 600;
        m_guiInfo.targetFPS = 60;
        m_guiInfo.lineThickness = 2.5f;
        m_guiInfo.margin = 20.0f;

        auto *p1 = new OGRID::Player("Player1", OGRID::Human);
        auto *p2 = new OGRID::Player("Player2", OGRID::Human);

        unsigned char dimensions;

        CLI_TRACE("Input the dimensions of the grid (3-10): ");
        dimensions = static_cast<unsigned char>(DURLIB::GIBI(3, 10));

        int choice = 0;
        while (choice == 0)
        {
            CLI_TRACE("\n1. Start as X\n2. Start as O\n3. Random");
            choice = DURLIB::GIBI(1, 3);
        }

        if (choice == 1)
        {
            SetRandomizeTurnOrder(false);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                     .setGameName("TicTacToe")
                                     .setGameDescription("TicTacToe Game")
                                     .setGrid(dimensions, dimensions)
                                     .setMaxPlayers(2)
                                     .addPlayer(p1)
                                     .addPlayer(p2)
                                     .build());
        }
        else if (choice == 2)
        {
            SetRandomizeTurnOrder(false);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                     .setGameName("TicTacToe")
                                     .setGameDescription("TicTacToe Game")
                                     .setGrid(dimensions, dimensions)
                                     .setMaxPlayers(2)
                                     .addPlayer(p2)
                                     .addPlayer(p1)
                                     .build());
        }
        else if (choice == 3)
        {
            SetRandomizeTurnOrder(true);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                     .setGameName("TicTacToe")
                                     .setGameDescription("TicTacToe Game")
                                     .setGrid(dimensions, dimensions)
                                     .setMaxPlayers(2)
                                     .addPlayer(p1)
                                     .addPlayer(p2)
                                     .build());
        }
    }

    // bool TicTacToe::IsWinningCondition(char playerChar)
    // {
    //     throw std::runtime_error("bool TicTacToe::IsWinningCondition(char playerChar) is not implemented.");
    // }

    void TicTacToe::OnGUIUpdateGridHover(Vector2 cell)
    {
        // Do nothing
    }
}

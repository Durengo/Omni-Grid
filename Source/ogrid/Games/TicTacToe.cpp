#include "TicTacToe.h"

#include <durlib.h>
#include <raylib.h>

namespace OGRID
{

    bool TicTacToe::TryMakeMove(unsigned char &row, unsigned char &col)
    {
        char gridChar = GetGameConfiguration()->grid->GetCharAt(row, col);
        if (GetGameConfiguration()->grid->GetCharAt(row, col) != GetGameConfiguration()->grid->GetDefaultChar())
        {
            CLI_WARN("Cannot make move at ({0}, {1}) because it is already occupied by {2}.", row, col, gridChar);
            return false;
        }

        GetGameConfiguration()->grid->SetCharAt(row, col, OGRID::MoveTypeEnumToChar(GetCurrentPlayer().ptr->GetPlayerMoveType()));

        // this->operator++();
        return true;
    }

    bool TicTacToe::IsWinningCondition(unsigned char row, unsigned char col)
    {
        Grid *grid = m_GameConfiguration->grid;
        char playerChar = grid->GetCharAt(row, col);
        return grid->CheckForRecurringCharsInRow(playerChar, 3) || grid->CheckForRecurringCharsInCol(playerChar, 3) ||
               grid->CheckForRecurringCharsInDiagonal(playerChar, 3) || grid->CheckForRecurringCharsInAntiDiagonal(playerChar, 3);
    }

    bool TicTacToe::IsDrawCondition(unsigned char row, unsigned char col)
    {
        // Check if all spots are filled.
        Grid *grid = m_GameConfiguration->grid;
        bool allSpotsFilled = true;
        for (int i = 0; i < grid->GetRows(); ++i)
        {
            for (int j = 0; j < grid->GetCols(); ++j)
            {
                if (grid->GetCharAt(i, j) == grid->GetDefaultChar())
                {
                    allSpotsFilled = false; // Found an empty spot, so not all spots are filled.
                    break;
                }
            }
            if (!allSpotsFilled)
                break;
        }

        // If all spots are filled and there's no win, then it's a draw.
        return allSpotsFilled && !IsWinningCondition(grid->GetLastChangedChar().first, grid->GetLastChangedChar().second);
    }

    void TicTacToe::SetupPlayers(const std::vector<OGRID::MoveType> &moveTypes)
    {
        size_t allowedPlayers = GetGameConfiguration()->maxPlayers;

        // CLI_ASSERT(GetGameConfiguration()->playerPairs.size() > allowedPlayers, "Player amount exceeds max player amount.");

        if (m_randomizeTurnOrder)
        {
            std::vector<OGRID::MoveType> shuffledMoveTypes = moveTypes;
            std::random_device rd;
            auto rng = std::default_random_engine{rd()};
            std::shuffle(shuffledMoveTypes.begin(), shuffledMoveTypes.end(), rng);

            for (int i = 0; i < GetGameConfiguration()->playerPairs.size(); i++)
            {
                GetGameConfiguration()->playerPairs[i].ptr->SetPlayerMoveType(shuffledMoveTypes[i % shuffledMoveTypes.size()]);
            }

            // Assuming MoveType::X is the MoveType that goes first.
            std::stable_sort(GetGameConfiguration()->playerPairs.begin(), GetGameConfiguration()->playerPairs.end(),
                             [](const OGRID::PlayerNameAndPtr &a, const OGRID::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetPlayerMoveType() == OGRID::MoveType::X;
                             });
        }
        else
        {
            for (int i = 0; i < GetGameConfiguration()->playerPairs.size(); i++)
            {
                GetGameConfiguration()->playerPairs[i].ptr->SetPlayerMoveType(moveTypes[i % moveTypes.size()]);
            }

            std::stable_sort(GetGameConfiguration()->playerPairs.begin(), GetGameConfiguration()->playerPairs.end(),
                             [](const OGRID::PlayerNameAndPtr &a, const OGRID::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetPlayerMoveType() == OGRID::MoveType::X;
                             });
        }
    }

    void TicTacToe::OnGUIUpdateGrid()
    {
        for (int i = 0; i < GetGameConfiguration()->grid->GetRows(); i++)
        {
            for (int j = 0; j < GetGameConfiguration()->grid->GetCols(); j++)
            {
                if (GetGrid()->GetCharAt(i, j) == OGRID::MoveTypeEnumToChar(OGRID::MoveType::X))
                {
                    DrawX(i, j);
                }
                else if (GetGrid()->GetCharAt(i, j) == OGRID::MoveTypeEnumToChar(OGRID::MoveType::O))
                {
                    DrawO(i, j);
                }
                else if (GetGrid()->GetCharAt(i, j) == GetGrid()->GetDefaultChar())
                {
                    continue;
                }
                else
                {
                    throw std::runtime_error("Invalid cell type.");
                }
            }
        }
    }

    void TicTacToe::DrawX(int row, int col)
    {
        float padding = m_guiInfo.margin; // Use the same margin for consistency

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
                                     .setGrid(dimensions, dimensions, '.')
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
                                     .setGrid(dimensions, dimensions, '.')
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
                                     .setGrid(dimensions, dimensions, '.')
                                     .setMaxPlayers(2)
                                     .addPlayer(p1)
                                     .addPlayer(p2)
                                     .build());
        }
    }

    bool TicTacToe::IsWinningCondition(char playerChar)
    {
        throw std::runtime_error("bool TicTacToe::IsWinningCondition(char playerChar) is not implemented.");
    }

    void TicTacToe::OnGUIUpdateGridHover(Vector2 cell)
    {
        // Do nothing
    }
}

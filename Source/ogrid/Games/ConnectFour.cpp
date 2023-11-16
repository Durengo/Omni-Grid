//
// Created by LastWeek on 16/11/2023.
//

#include <durlib/Log/Log.h>
#include <durlib/Input/Input.h>
#include <random>
#include "ConnectFour.h"

namespace OGRID{
    bool ConnectFour::TryMakeMove(unsigned char &row, unsigned char &col) {
        // Check if the column is occupied and find the topmost available spot
        if (!IsColumnOccupied(col, row))
        {
            CLI_WARN("Cannot make move at column {0}, because it is fully occupied", col);
            return false;
        }

        // Set the player's move in the grid
        GetGameConfiguration()->grid->SetCharAt(row, col, OGRID::MoveTypeEnumToChar(GetCurrentPlayer().ptr->GetPlayerMoveType()));

        // this->operator++();
        return true;
    }

    bool ConnectFour::IsWinningCondition(unsigned char row, unsigned char col) {
        char playerChar = GetGameConfiguration()->grid->GetCharAt(row, col);
        return GetGameConfiguration()->grid->CheckForRecurringCharsInRow(playerChar, 4) || GetGameConfiguration()->grid->CheckForRecurringCharsInCol(playerChar, 4) ||
               GetGameConfiguration()->grid->CheckForRecurringCharsInDiagonal(playerChar, 4) || GetGameConfiguration()->grid->CheckForRecurringCharsInAntiDiagonal(playerChar, 4);
    }

    bool ConnectFour::IsWinningCondition(char playerChar) {
        throw std::runtime_error("bool ConnectFour::IsWinningCondition(char playerChar) is not implemented.");
    }

    bool ConnectFour::IsDrawCondition(unsigned char row, unsigned char col) {
        // Check if all spots are filled.
        bool allSpotsFilled = true;
        for (int i = 0; i < GetGameConfiguration()->grid->GetRows(); ++i)
        {
            for (int j = 0; j < GetGameConfiguration()->grid->GetCols(); ++j)
            {
                if (GetGameConfiguration()->grid->GetCharAt(i, j) == GetGameConfiguration()->grid->GetDefaultChar())
                {
                    allSpotsFilled = false; // Found an empty spot, so not all spots are filled.
                    break;
                }
            }
            if (!allSpotsFilled)
                break;
        }

        // If all spots are filled and there's no win, then it's a draw.
        return allSpotsFilled && !IsWinningCondition(GetGameConfiguration()->grid->GetLastChangedChar().first, GetGameConfiguration()->grid->GetLastChangedChar().second);
    }

    void ConnectFour::SetupPlayers(const std::vector<OGRID::MoveType> &moveTypes) {
        size_t allowedPlayers = GetGameConfiguration()->maxPlayers;

        //CLI_ASSERT(m_Players.size() > allowedPlayers, "Player amount exceeds max player amount.");

        if (m_randomizeTurnOrder)
        {
            std::vector<OGRID::MoveType> shuffledMoveTypes = moveTypes;
            std::random_device rd;
            auto rng = std::default_random_engine{rd()};
            std::shuffle(shuffledMoveTypes.begin(), shuffledMoveTypes.end(), rng);

            for (int i = 0; i < m_Players.size(); i++)
            {
                m_Players[i].ptr->SetPlayerMoveType(shuffledMoveTypes[i % shuffledMoveTypes.size()]);
            }

            // Assuming MoveType::X is the MoveType that goes first.
            std::stable_sort(m_Players.begin(), m_Players.end(),
                             [](const OGRID::PlayerNameAndPtr &a, const OGRID::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetPlayerMoveType() == OGRID::MoveType::X;
                             });
        }
        else
        {
            for (int i = 0; i < m_Players.size(); i++)
            {
                m_Players[i].ptr->SetPlayerMoveType(moveTypes[i % moveTypes.size()]);
            }

            std::stable_sort(m_Players.begin(), m_Players.end(),
                             [](const OGRID::PlayerNameAndPtr &a, const OGRID::PlayerNameAndPtr &b)
                             {
                                 return a.ptr->GetPlayerMoveType() == OGRID::MoveType::X;
                             });
        }
    }

    void ConnectFour::Initialize() {
        m_guiInfo = *new GUIInfo();
        m_guiInfo.windowName = "ConnectFour";
        m_guiInfo.width = 800;
        m_guiInfo.height = 600;
        m_guiInfo.targetFPS = 60;
        m_guiInfo.lineThickness = 2.5f;
        m_guiInfo.margin = 40.0f;
        m_guiInfo.gridSize = 7;

        auto *p1 = new OGRID::Player("Player1", OGRID::Human);
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
            p1->SetPlayerMoveType(OGRID::MoveType::X);
            p2->SetPlayerMoveType(OGRID::MoveType::O);
            SetRandomizeTurnOrder(false);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
            .setGameName("ConnectFour")
            .setGameDescription("ConnectFour Game")
            .setGrid(7, 6, '.')
            .setMaxPlayers(2)
            .addPlayer(p1)
            .addPlayer(p2)
            .build());
        }
        else if (choice == 2)
        {
            p1->SetPlayerMoveType(OGRID::MoveType::O);
            p2->SetPlayerMoveType(OGRID::MoveType::X);
            SetRandomizeTurnOrder(false);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                         .setGameName("ConnectFour")
                                         .setGameDescription("ConnectFour Game")
                                         .setGrid(7, 6, '.')
                                         .setMaxPlayers(2)
                                         .addPlayer(p1)
                                         .addPlayer(p2)
                                         .build());
        }
        else if (choice == 3)
        {
            SetRandomizeTurnOrder(true);
            SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                         .setGameName("ConnectFour")
                                         .setGameDescription("ConnectFour Game")
                                         .setGrid(7, 6, '.')
                                         .setMaxPlayers(2)
                                         .addPlayer(p1)
                                         .addPlayer(p2)
                                         .build());
        }
    }

    void ConnectFour::OnGUIUpdateGrid() {
        for (int i = 0; i < GetGameConfiguration()->grid->GetRows(); i++)
        {
            for (int j = 0; j < GetGameConfiguration()->grid->GetCols(); j++)
            {
                if (GetGrid()->GetCharAt(i, j) == OGRID::MoveTypeEnumToChar(OGRID::MoveType::X))
                {
                    DrawCircle(i, j, RED, false);
                }
                else if (GetGrid()->GetCharAt(i, j) == OGRID::MoveTypeEnumToChar(OGRID::MoveType::O))
                {
                    DrawCircle(i, j, BLACK, false);
                }
                else if (GetGrid()->GetCharAt(i, j) == GetGrid()->GetDefaultChar())
                {
                    continue; // Empty cell, do nothing
                }
                else
                {
                    throw std::runtime_error("Invalid cell type.");
                }
            }
        }
    }

    void ConnectFour::OnGUIUpdateGridHover(Vector2 cell) {
        if (cell.x != -1 && cell.y != -1)
        {
            int col = static_cast<int>(cell.x);
            int row = GetTopMostPiecePositionInColumn(col) - 1;

            if (row >= 0 && row < GetGrid()->GetRows())
            {
                if (GetCurrentPlayer().ptr->GetPlayerMoveType() == OGRID::MoveType::X)
                {
                    DrawCircle(row, col, RED, true);
                }
                else if (GetCurrentPlayer().ptr->GetPlayerMoveType() == OGRID::MoveType::O)
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

    void ConnectFour::DrawCircle(int row, int col, Color color, bool blinking) {
        float padding = m_guiInfo.margin; // Use the same margin for consistency

        // Calculate offsets for non-square windows (same as in DrawGrid)
        float xOffset = (m_guiInfo.width - (m_guiInfo.cellSize * m_guiInfo.gridSize)) / 2.0f;
        float yOffset = (m_guiInfo.height - (m_guiInfo.cellSize * m_guiInfo.gridSize)) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Calculate the center of the circle
        float centerX = xOffset + (col + 0.5f) * m_guiInfo.cellSize;
        float centerY = yOffset + (row + 0.5f) * m_guiInfo.cellSize;

        // Calculate the radius of the circle based on cell size and padding
        float radius = m_guiInfo.cellSize / 2.0f;

        if (blinking){
            if (alpha == 1.0f || alpha == 0.0f)
            {
                alphaSpeed = -alphaSpeed; // Invert the speed
            }
            alpha += alphaSpeed;
            alpha = std::clamp(alpha, 0.0f, 1.0f);
            DrawCircleV(Vector2{centerX, centerY}, radius, Fade(color, alpha));
        } else {
            DrawCircleV(Vector2{centerX, centerY}, radius, color);
        }
    }
}


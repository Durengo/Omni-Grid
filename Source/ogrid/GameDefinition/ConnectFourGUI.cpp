#include "ConnectFourGUI.h"

#include <durlib.h>
#include <ogrid.h>
#include <ogrid_gui.h>
#include <raylib.h>

#include "GameDefinition/ConnectFourLogic.h"
#include "GameDefinition/ConnectFourInstance.h"
#include "GameDefinition/ConnectFourGUIInstance.h"

namespace OGRIDSandbox
{
    ConnectFourGUI *instance = ConnectFourGUIInstance::GetInstance();
    ConnectFourLogic *ConnectFourGUI::i_gameLogic;
    bool ConnectFourGUI::i_randomizeFirstPlayer{true};

    // Constructors & Destructors
    ConnectFourGUI::ConnectFourGUI()
    {
        instance->i_gameLogic = ConnectFourInstance::GetInstance();
    }

    ConnectFourGUI::~ConnectFourGUI()
    {
        if (instance->i_gameLogic != nullptr)
        {
            instance->i_gameLogic = nullptr;
            ConnectFourInstance::DeleteInstance();
        }
    }

    ConnectFourLogic *ConnectFourGUI::GetGameLogic()
    {
        return instance->i_gameLogic;
    }

    void ConnectFourGUI::SetGameConfiguration(OGRID::GameConfiguration *gameConfiguration)
    {
        DEBUG_ASSERT(instance->i_gameLogic, "TicTacToeLogic instance not initialized.");

        instance->i_gameLogic->SetGameConfiguration(gameConfiguration);

        instance->m_gridSize = instance->i_gameLogic->GetGrid()->GetRows();
    }

    void ConnectFourGUI::SetRandomizeFirstPlayer(bool randomizeFirstPlayer)
    {
        instance->i_randomizeFirstPlayer = randomizeFirstPlayer;
    }

    void ConnectFourGUI::DrawGrid()
    {
        // Set the desired padding around the grid
        float padding = instance->m_margin;

        // Calculate the size of the cells to fit the grid in the window, accounting for padding
        instance->m_cellSize = (std::min(instance->m_windowResolution.width, instance->m_windowResolution.height) - (2 * padding)) / static_cast<float>(instance->m_gridSize);

        // Calculate any necessary offsets if the window is not square
        float xOffset = (instance->m_windowResolution.width - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        float yOffset = (instance->m_windowResolution.height - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;

        // Adjust offsets for padding
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Draw vertical lines
        for (int i = 0; i <= instance->m_gridSize; i++)
        {
            float lineX = xOffset + i * instance->m_cellSize;
            DrawLine(lineX, yOffset, lineX, yOffset + instance->m_cellSize * instance->m_gridSize, GRAY);
        }

        // Draw horizontal lines
        for (int i = 0; i <= instance->m_gridSize; i++)
        {
            float lineY = yOffset + i * instance->m_cellSize;
            DrawLine(xOffset, lineY, xOffset + instance->m_cellSize * instance->m_gridSize, lineY, GRAY);
        }

        // Iterate over the grid state and draw 'X' or 'O' as needed
        for (int i = 0; i < instance->m_gridSize; i++)
        {
            for (int j = 0; j < instance->m_gridSize; j++)
            {
                if (instance->i_gameLogic->GetGrid()->GetCharAt(i, j) == OGRID::MoveTypeEnumToChar(OGRID::MoveType::X))
                {
                    instance->DrawRED(i, j);
                }
                else if (instance->i_gameLogic->GetGrid()->GetCharAt(i, j) == OGRID::MoveTypeEnumToChar(OGRID::MoveType::O))
                {
                    instance->DrawBLACK(i, j);
                }
                else if (instance->i_gameLogic->GetGrid()->GetCharAt(i, j) == instance->i_gameLogic->GetGrid()->GetDefaultChar())
                {
                    continue; // Empty cell, do nothing
                }
                else
                {
                    throw std::runtime_error("Invalid cell type.");
                }
            }
        }

        // If the mouse is over a column, get the last empty cell in that column and draw a blinking circle dependent on player turn (Red or Black)
        Vector2 mouseCell = GetCellFromMouse(GetMousePosition());
        if (mouseCell.x != -1 && mouseCell.y != -1)
        {
            int col = static_cast<int>(mouseCell.x);
            int row = instance->i_gameLogic->GetTopMostPiecePositionInColumn(col) - 1;

            if (row >= 0 && row < instance->m_gridSize)
            {
                if (instance->i_gameLogic->GetGameConfiguration()->turnManager->GetCurrentPlayer().ptr->GetPlayerMoveType() == OGRID::MoveType::X)
                {
                    instance->DrawREDBlinking(row, col);
                }
                else if (instance->i_gameLogic->GetGameConfiguration()->turnManager->GetCurrentPlayer().ptr->GetPlayerMoveType() == OGRID::MoveType::O)
                {
                    instance->DrawBLACKBlinking(row, col);
                }
                else
                {
                    throw std::runtime_error("Invalid player move type.");
                }
            }
        }
    }

    Vector2 ConnectFourGUI::GetCellFromMouse(Vector2 mousePosition)
    {
        // Calculate the starting point of the grid on the screen
        float gridStartX = (instance->m_windowResolution.width - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        float gridStartY = (instance->m_windowResolution.height - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;

        // Adjust the mouse position by subtracting the starting point of the grid
        float adjustedMouseX = mousePosition.x - gridStartX;
        float adjustedMouseY = mousePosition.y - gridStartY;

        // Check if the adjusted mouse position is outside the bounds of the grid
        if (adjustedMouseX < 0 || adjustedMouseY < 0 || adjustedMouseX >= (instance->m_cellSize * instance->m_gridSize) || adjustedMouseY >= (instance->m_cellSize * instance->m_gridSize))
        {
            // Outside of grid bounds, return an invalid cell position
            return Vector2(-1, -1);
        }

        // Convert the adjusted mouse position to cell indices
        int cellIndexX = static_cast<int>(adjustedMouseX / instance->m_cellSize);
        int cellIndexY = static_cast<int>(adjustedMouseY / instance->m_cellSize);

        // The Y coordinate needs to be inverted because the 2D array (0,0) starts at the top-left
        // but in screen coordinates, Y increases as you go down.
        // Since we are not using an upside-down grid, we don't invert Y.

        return Vector2(static_cast<float>(cellIndexX), static_cast<float>(cellIndexY));
    }

    void ConnectFourGUI::DrawRED(int row, int col)
    {
        float padding = instance->m_margin; // Use the same margin for consistency

        // Calculate offsets for non-square windows (same as in DrawGrid)
        float xOffset = (instance->m_windowResolution.width - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        float yOffset = (instance->m_windowResolution.height - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Calculate the center of the circle
        float centerX = xOffset + (col + 0.5f) * instance->m_cellSize;
        float centerY = yOffset + (row + 0.5f) * instance->m_cellSize;

        // Calculate the radius of the circle based on cell size and padding
        float radius = instance->m_cellSize / 2.0f;

        // Draw the filled red circle
        DrawCircleV(Vector2{centerX, centerY}, radius, RED);
    }

    void ConnectFourGUI::DrawBLACK(int row, int col)
    {
        float padding = instance->m_margin; // Use the same margin for consistency

        // Calculate offsets for non-square windows (same as in DrawGrid)
        float xOffset = (instance->m_windowResolution.width - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        float yOffset = (instance->m_windowResolution.height - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Calculate the center of the circle
        float centerX = xOffset + (col + 0.5f) * instance->m_cellSize;
        float centerY = yOffset + (row + 0.5f) * instance->m_cellSize;

        // Calculate the radius of the circle based on cell size and padding
        float radius = instance->m_cellSize / 2.0f;

        // Draw the filled red circle
        DrawCircleV(Vector2{centerX, centerY}, radius, BLACK);
    }

    void ConnectFourGUI::ChangeTurnOrder()
    {
        int choice = 0;
        while (choice == 0)
        {
            CLI_TRACE("\n1. Start as RED\n2. Start as BLACK\n3. Random");
            choice = DURLIB::GIBI(1, 3);
        }

        if (choice == 1)
        {
            if (instance->i_gameLogic->GetPlayers()[0]->GetPlayerName() == "Player1")
            {
                instance->i_gameLogic->GetPlayers()[0]->SetPlayerMoveType(OGRID::MoveType::X);
                instance->i_gameLogic->GetPlayers()[1]->SetPlayerMoveType(OGRID::MoveType::O);
            }
            else
            {
                instance->i_gameLogic->GetPlayers()[0]->SetPlayerMoveType(OGRID::MoveType::O);
                instance->i_gameLogic->GetPlayers()[1]->SetPlayerMoveType(OGRID::MoveType::X);
                instance->i_gameLogic->SwapPlayerPositions();
            }

            instance->SetRandomizeFirstPlayer(false);
        }
        else if (choice == 2)
        {
            if (instance->i_gameLogic->GetPlayers()[0]->GetPlayerName() == "Player1")
            {
                instance->i_gameLogic->GetPlayers()[0]->SetPlayerMoveType(OGRID::MoveType::O);
                instance->i_gameLogic->GetPlayers()[1]->SetPlayerMoveType(OGRID::MoveType::X);
            }
            else
            {
                instance->i_gameLogic->GetPlayers()[0]->SetPlayerMoveType(OGRID::MoveType::X);
                instance->i_gameLogic->GetPlayers()[1]->SetPlayerMoveType(OGRID::MoveType::O);
                instance->i_gameLogic->SwapPlayerPositions();
            }

            // i_instance->i_gameLogic->GetPlayers()[0]->SetPlayerMoveType(Sandbox::MoveType::O);
            // i_instance->i_gameLogic->GetPlayers()[1]->SetPlayerMoveType(Sandbox::MoveType::X);

            // Sandbox::Player *temp = i_instance->i_gameLogic->GetPlayers()[1];
            // i_instance->i_gameLogic->GetPlayers()[1] = i_instance->i_gameLogic->GetPlayers()[0];
            // i_instance->i_gameLogic->GetPlayers()[0] = temp;

            instance->SetRandomizeFirstPlayer(false);
        }
        else if (choice == 3)
        {
            instance->SetRandomizeFirstPlayer(true);
        }

        switch (instance->i_randomizeFirstPlayer)
        {
        case true:
            instance->i_gameLogic->SetRandomizeTurnOrder(true);
            break;
        case false:
            instance->i_gameLogic->SetRandomizeTurnOrder(false);
            break;
        }

        unsigned int dimension = instance->i_gameLogic->GetGrid()->GetRows();
        char defaultChar = instance->i_gameLogic->GetGrid()->GetDefaultChar();

        instance->i_gameLogic->GetGameConfiguration()->grid->ResetGridWithNewSize(dimension, dimension, defaultChar);
    }

    void ConnectFourGUI::InitializeWindow(std::string windowName, int screenWidth, int screenHeight, int targetFPS)
    {
        instance->m_windowName = windowName;
        instance->m_windowResolution.width = screenWidth;
        instance->m_windowResolution.height = screenHeight;
        instance->m_targetFPS = targetFPS;

        instance->m_lineThickness = 2.5f;
        instance->m_margin = 40.0f;
        // i_instance->m_gridSize = gridSize;
        // i_instance->m_cellSize = static_cast<float>(i_instance->m_windowResolution.width) / i_instance->m_gridSize;
        // i_instance->m_cellSize = std::min(i_instance->m_windowResolution.width, i_instance->m_windowResolution.height) / static_cast<float>(i_instance->m_gridSize);

        SetConfigFlags(FLAG_WINDOW_RESIZABLE);

        InitWindow(m_windowResolution.width, m_windowResolution.height, m_windowName.c_str());

        SetTargetFPS(m_targetFPS);
    }

    void ConnectFourGUI::BeginMainLoop()
    {
        DEBUG_ASSERT(instance->i_gameLogic, "ConnectFourLogic instance not initialized.");

        switch (instance->i_randomizeFirstPlayer)
        {
        case true:
            instance->i_gameLogic->SetRandomizeTurnOrder(true);
            break;
        case false:
            instance->i_gameLogic->SetRandomizeTurnOrder(false);
            break;
        }

        instance->i_gameLogic->SetupGame();
        instance->i_gameLogic->StartGame();

        OGRID::Button restartButton(
            {static_cast<float>(instance->m_windowResolution.width) / 2 - 100,
             static_cast<float>(instance->m_windowResolution.height) / 2 + 30, 200, 40},
            GRAY, DARKGRAY, LIGHTGRAY, []()
            {
                    CLI_TRACE("Restarting game...");
                    instance->i_gameLogic->ResetGame();
                    instance->i_gameLogic->SetGameState(OGRID::GameState::InProgress); },
            "Restart", false);

        // Button changeTurnOrderButton(
        //     {static_cast<float>(i_instance->m_windowResolution.width) / 2 - 100, static_cast<float>(i_instance->m_windowResolution.height) / 2 + 150, 200, 40},
        //     GRAY, DARKGRAY, LIGHTGRAY, []()
        //     {
        //         CLI_TRACE("Changing Turn Order");
        //         i_instance->ChangeTurnOrder();

        //         i_instance->i_gameLogic->ResetGame();
        //         i_instance->i_gameLogic->SetGameState(Sandbox::GameState::InProgress); },
        //     "Change Turns", false);

        OGRID::Text gameOverText("Game Over!", 20, 0, 100, BLACK, OGRID::Justify::CENTER_X, instance->m_windowResolution.width, instance->m_windowResolution.height);

        OGRID::Text winnerText("Winner: ", 20, 0, 150, BLACK, OGRID::Justify::CENTER_X, instance->m_windowResolution.width, instance->m_windowResolution.height);

        OGRID::Text currentPlayerText("Current Player: ", 8, 5, 5, BLACK, OGRID::Justify::NONE, instance->m_windowResolution.width, instance->m_windowResolution.height);
        OGRID::Text turnText("Turn: ", 8, 5, 20, BLACK, OGRID::Justify::NONE, instance->m_windowResolution.width, instance->m_windowResolution.height);

        OGRID::Text drawText("Draw!", 20, 0, 100, BLACK, OGRID::Justify::CENTER_X, instance->m_windowResolution.width, instance->m_windowResolution.height);

        while (!WindowShouldClose()) // Detect window close button or ESC key
        {
            instance->m_windowResolution.width = GetScreenWidth();
            instance->m_windowResolution.height = GetScreenHeight();
            // Update
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && instance->i_gameLogic->GetGameState() != OGRID::GameState::GameOver)
            {
                Vector2 cell = GetCellFromMouse(GetMousePosition());

                try
                {
                    if (cell.x == -1 || cell.y == -1)
                        throw std::runtime_error("Invalid cell position.");
                    else
                        instance->i_gameLogic->MakeMove((unsigned char)cell.y, (unsigned char)cell.x);
                }
                catch (const std::runtime_error &e)
                {
                    CLI_WARN(e.what());
                }
                catch (const std::exception &e)
                {
                    CLI_FATAL(e.what());
                }
            }

            restartButton.Update();
            // changeTurnOrderButton.Update();

            // Draw
            BeginDrawing();
            ClearBackground(RAYWHITE);

            std::string move;

            if (instance->i_gameLogic->GetGameState() == OGRID::GameState::InProgress)
            {
                move = OGRID::MoveTypeEnumToString(instance->i_gameLogic->GetGameConfiguration()->turnManager->GetCurrentPlayer().ptr->GetPlayerMoveType());
                if (move == "X")
                {                 //************************
                    move = "RED"; //
                }
                else
                {                   // X AND O UNTIL BETTER SOLUTION (never)
                    move = "BLACK"; //
                }                   //***********************

                restartButton.isEnabled = false;
                // changeTurnOrderButton.isEnabled = false;

                DrawGrid();
                currentPlayerText.SetText("Current Player: " + instance->i_gameLogic->GetGameConfiguration()->turnManager->GetCurrentPlayer().ptr->GetPlayerName());
                turnText.SetText("Turn: " + move);
                currentPlayerText.Draw();
                turnText.Draw();
            }
            else if (instance->i_gameLogic->GetGameState() == OGRID::GameState::GameOver)
            {
                if (instance->i_gameLogic->GetGameOverType() == OGRID::GameOverType::Win)
                {
                    move = OGRID::MoveTypeEnumToString(instance->i_gameLogic->GetWinner()->GetPlayerMoveType());
                    if (move == "X")
                    {                 //************************
                        move = "RED"; //
                    }
                    else
                    {                   // X AND O UNTIL BETTER SOLUTION (never)
                        move = "BLACK"; //
                    }                   //***********************

                    restartButton.isEnabled = true;
                    // changeTurnOrderButton.isEnabled = true;

                    winnerText.SetText("Winner: " + instance->i_gameLogic->GetWinner()->GetPlayerName() + " (" + move + ")");
                    gameOverText.Draw();
                    winnerText.Draw();
                    restartButton.Draw();
                    ;
                    // changeTurnOrderButton.Draw();
                }
                else if (instance->i_gameLogic->GetGameOverType() == OGRID::GameOverType::Draw)
                {
                    restartButton.isEnabled = true;
                    // changeTurnOrderButton.isEnabled = true;

                    drawText.Draw();
                    restartButton.Draw();
                    // changeTurnOrderButton.Draw();
                }
            }

            EndDrawing();
        }

        CloseWindow();
    }

    void ConnectFourGUI::DrawREDBlinking(int row, int col)
    {
        float padding = instance->m_margin;
        float xOffset = (instance->m_windowResolution.width - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        float yOffset = (instance->m_windowResolution.height - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        float centerX = xOffset + (col + 0.5f) * instance->m_cellSize;
        float centerY = yOffset + (row + 0.5f) * instance->m_cellSize;
        float radius = instance->m_cellSize / 2.0f;

        if (alpha == 1.0f)
        {
            alphaSpeed = -alphaSpeed;
        }
        else if (alpha == 0.0f)
        {
            alphaSpeed = -alphaSpeed;
        }
        alpha += alphaSpeed;
        alpha = std::clamp(alpha, 0.0f, 1.0f);

        DrawCircleV(Vector2{centerX, centerY}, radius, Fade(RED, alpha));
    }

    void ConnectFourGUI::DrawBLACKBlinking(int row, int col)
    {
        float padding = instance->m_margin;
        float xOffset = (instance->m_windowResolution.width - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        float yOffset = (instance->m_windowResolution.height - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        float centerX = xOffset + (col + 0.5f) * instance->m_cellSize;
        float centerY = yOffset + (row + 0.5f) * instance->m_cellSize;
        float radius = instance->m_cellSize / 2.0f;

        if (alpha == 1.0f)
        {
            alphaSpeed = -alphaSpeed;
        }
        else if (alpha == 0.0f)
        {
            alphaSpeed = -alphaSpeed;
        }
        alpha += alphaSpeed;
        alpha = std::clamp(alpha, 0.0f, 1.0f);

        DrawCircleV(Vector2{centerX, centerY}, radius, Fade(BLACK, alpha));
    }
}
#include "TicTacToeGUI.h"

#include <durlib.h>
#include <ogrid_gui.h>

#include <raylib.h>
#include <GameLogic/TicTacToeLogic.h>
#include <GameLogic/TicTacToeInstance.h>
#include "GUI/TicTacToeGUIInstance.h"

namespace OGRIDSandbox
{
    TicTacToeGUI* instance = TicTacToeGUIInstance::GetInstance();
    TicTacToeLogic *TicTacToeGUI::i_gameLogic;
    bool TicTacToeGUI::i_randomizeFirstPlayer{true};

    // Constructors & Destructors
    TicTacToeGUI::TicTacToeGUI()
    {
        instance->i_gameLogic = TicTacToeInstance::GetInstance();
    }

    TicTacToeGUI::~TicTacToeGUI()
    {
        if (instance->i_gameLogic != nullptr)
        {
            instance->i_gameLogic = nullptr;
            TicTacToeInstance::DeleteInstance();
        }
    }

    // Getters & Setters

    TicTacToeLogic *TicTacToeGUI::GetGameLogic()
    {
        return instance->i_gameLogic;
    }

    void TicTacToeGUI::SetGameConfiguration(GENERICS::GameConfiguration *gameConfiguration)
    {
        DEBUG_ASSERT(instance->i_gameLogic, "TicTacToeLogic instance not initialized.");

        instance->i_gameLogic->SetGameConfiguration(gameConfiguration);

        instance->m_gridSize = instance->i_gameLogic->GetGrid()->GetRows();
    }

    void TicTacToeGUI::SetRandomizeFirstPlayer(bool randomizeFirstPlayer)
    {
        instance->i_randomizeFirstPlayer = randomizeFirstPlayer;
    }

    // Private methods

    void TicTacToeGUI::DrawGrid()
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
                if (instance->i_gameLogic->GetGrid()->GetCharAt(i, j) == GENERICS::MoveTypeEnumToChar(GENERICS::MoveType::X))
                {
                    instance->DrawX(i, j);
                }
                else if (instance->i_gameLogic->GetGrid()->GetCharAt(i, j) == GENERICS::MoveTypeEnumToChar(GENERICS::MoveType::O))
                {
                    instance->DrawO(i, j);
                }
                else if (instance->i_gameLogic->GetGrid()->GetCharAt(i, j) == instance->i_gameLogic->GetGrid()->GetDefaultChar())
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

    Vector2 TicTacToeGUI::GetCellFromMouse(Vector2 mousePosition)
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

    void TicTacToeGUI::DrawX(int row, int col)
    {
        float padding = instance->m_margin; // Use the same margin for consistency

        // Calculate offsets for non-square windows (same as in DrawGrid)
        float xOffset = (instance->m_windowResolution.width - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        float yOffset = (instance->m_windowResolution.height - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Calculate the starting and ending points for the two lines of the X
        float startX = xOffset + col * instance->m_cellSize + padding;
        float startY = yOffset + row * instance->m_cellSize + padding;
        float endX = xOffset + (col + 1) * instance->m_cellSize - padding;
        float endY = yOffset + (row + 1) * instance->m_cellSize - padding;

        // Draw the first diagonal line of the X
        DrawLine(startX, startY, endX, endY, BLACK);

        // Draw the second diagonal line of the X
        DrawLine(startX, endY, endX, startY, BLACK);
    }

    void TicTacToeGUI::DrawO(int row, int col)
    {
        // Use the same margin for consistency and to make sure 'O' is within the cell bounds
        float padding = instance->m_margin;

        // Calculate offsets for non-square windows (same as in DrawGrid)
        float xOffset = (instance->m_windowResolution.width - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        float yOffset = (instance->m_windowResolution.height - (instance->m_cellSize * instance->m_gridSize)) / 2.0f;
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Radius of 'O' should probably be a bit less than half the cell size to fit within the cell,
        // minus some padding to avoid touching the cell borders.
        float radius = (instance->m_cellSize / 2) - padding;

        // Center point calculations now include the offset and padding
        float centerX = xOffset + col * instance->m_cellSize + (instance->m_cellSize / 2);
        float centerY = yOffset + row * instance->m_cellSize + (instance->m_cellSize / 2);

        DrawCircleLines(centerX, centerY, radius, BLACK);
    }

    void TicTacToeGUI::ChangeGridLayout()
    {
        CLI_TRACE("Input the dimensions of the grid (3-10): ");
        auto dimensions = static_cast<unsigned char>(DURLIB::GIBI(3, 10));
        m_gridSize = dimensions;

        instance->i_gameLogic->GetGameConfiguration()->grid->ResetGridWithNewSize(dimensions, dimensions, '.');
    }

    void TicTacToeGUI::ChangeTurnOrder()
    {
        int choice = 0;
        while (choice == 0)
        {
            CLI_TRACE("\n1. Start as X\n2. Start as O\n3. Random");
            choice = DURLIB::GIBI(1, 3);
        }

        if (choice == 1)
        {
            if (instance->i_gameLogic->GetPlayers()[0]->GetPlayerName() == "Player1")
            {
                instance->i_gameLogic->GetPlayers()[0]->SetPlayerMoveType(GENERICS::MoveType::X);
                instance->i_gameLogic->GetPlayers()[1]->SetPlayerMoveType(GENERICS::MoveType::O);
            }
            else
            {
                instance->i_gameLogic->GetPlayers()[0]->SetPlayerMoveType(GENERICS::MoveType::O);
                instance->i_gameLogic->GetPlayers()[1]->SetPlayerMoveType(GENERICS::MoveType::X);
                instance->i_gameLogic->SwapPlayerPositions();
            }

            instance->SetRandomizeFirstPlayer(false);
        }
        else if (choice == 2)
        {
            if (instance->i_gameLogic->GetPlayers()[0]->GetPlayerName() == "Player1")
            {
                instance->i_gameLogic->GetPlayers()[0]->SetPlayerMoveType(GENERICS::MoveType::O);
                instance->i_gameLogic->GetPlayers()[1]->SetPlayerMoveType(GENERICS::MoveType::X);
            }
            else
            {
                instance->i_gameLogic->GetPlayers()[0]->SetPlayerMoveType(GENERICS::MoveType::X);
                instance->i_gameLogic->GetPlayers()[1]->SetPlayerMoveType(GENERICS::MoveType::O);
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

    // Public methods

    void TicTacToeGUI::InitializeWindow(std::string windowName, int screenWidth, int screenHeight, int targetFPS)
    {
        instance->m_windowName = windowName;
        instance->m_windowResolution.width = screenWidth;
        instance->m_windowResolution.height = screenHeight;
        instance->m_targetFPS = targetFPS;

        instance->m_lineThickness = 2.5f;
        instance->m_margin = 20.0f;
        // i_instance->m_gridSize = gridSize;
        // i_instance->m_cellSize = static_cast<float>(i_instance->m_windowResolution.width) / i_instance->m_gridSize;
        // i_instance->m_cellSize = std::min(i_instance->m_windowResolution.width, i_instance->m_windowResolution.height) / static_cast<float>(i_instance->m_gridSize);

        SetConfigFlags(FLAG_WINDOW_RESIZABLE);

        InitWindow(m_windowResolution.width, m_windowResolution.height, m_windowName.c_str());

        SetTargetFPS(m_targetFPS);
    }

    void TicTacToeGUI::BeginMainLoop()
    {
        DEBUG_ASSERT(instance->i_gameLogic, "TicTacToeLogic instance not initialized.");

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

        Sandbox::Button restartButton(
            {static_cast<float>(instance->m_windowResolution.width) / 2 - 100,
             static_cast<float>(instance->m_windowResolution.height) / 2 + 30, 200, 40},
            GRAY, DARKGRAY, LIGHTGRAY, []()
            {
                CLI_TRACE("Restarting game...");
                instance->i_gameLogic->ResetGame();
                instance->i_gameLogic->SetGameState(GENERICS::GameState::InProgress); },
            "Restart", false);

        Sandbox::Button changeGridButton(
            {static_cast<float>(instance->m_windowResolution.width) / 2 - 100,
             static_cast<float>(instance->m_windowResolution.height) / 2 + 90, 200, 40},
            GRAY, DARKGRAY, LIGHTGRAY, []()
            {
                CLI_TRACE("Changing Grid Layout");
                instance->ChangeGridLayout();

                instance->i_gameLogic->ResetGame();
                instance->i_gameLogic->SetGameState(GENERICS::GameState::InProgress); },
            "Change Grid", false);

        // Button changeTurnOrderButton(
        //     {static_cast<float>(i_instance->m_windowResolution.width) / 2 - 100, static_cast<float>(i_instance->m_windowResolution.height) / 2 + 150, 200, 40},
        //     GRAY, DARKGRAY, LIGHTGRAY, []()
        //     {
        //         CLI_TRACE("Changing Turn Order");
        //         i_instance->ChangeTurnOrder();

        //         i_instance->i_gameLogic->ResetGame();
        //         i_instance->i_gameLogic->SetGameState(Sandbox::GameState::InProgress); },
        //     "Change Turns", false);

        Sandbox::Text gameOverText("Game Over!", 20, 0, 100, BLACK, Sandbox::Justify::CENTER_X, instance->m_windowResolution.width, instance->m_windowResolution.height);

        Sandbox::Text winnerText("Winner: ", 20, 0, 150, BLACK, Sandbox::Justify::CENTER_X, instance->m_windowResolution.width, instance->m_windowResolution.height);

        Sandbox::Text currentPlayerText("Current Player: ", 8, 5, 5, BLACK, Sandbox::Justify::NONE, instance->m_windowResolution.width, instance->m_windowResolution.height);
        Sandbox::Text turnText("Turn: ", 8, 5, 20, BLACK, Sandbox::Justify::NONE, instance->m_windowResolution.width, instance->m_windowResolution.height);

        Sandbox::Text drawText("Draw!", 20, 0, 100, BLACK, Sandbox::Justify::CENTER_X, instance->m_windowResolution.width, instance->m_windowResolution.height);

        while (!WindowShouldClose()) // Detect window close button or ESC key
        {
            instance->m_windowResolution.width = GetScreenWidth();
            instance->m_windowResolution.height = GetScreenHeight();
            // Update
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && instance->i_gameLogic->GetGameState() != GENERICS::GameState::GameOver)
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
            changeGridButton.Update();
            // changeTurnOrderButton.Update();

            // Draw
            BeginDrawing();
            ClearBackground(RAYWHITE);
            if (instance->i_gameLogic->GetGameState() == GENERICS::GameState::InProgress)
            {
                restartButton.isEnabled = false;
                changeGridButton.isEnabled = false;
                // changeTurnOrderButton.isEnabled = false;

                DrawGrid();
                currentPlayerText.SetText("Current Player: " + instance->i_gameLogic->GetGameConfiguration()->turnManager->GetCurrentPlayer().ptr->GetPlayerName());
                turnText.SetText("Turn: " + GENERICS::MoveTypeEnumToString(instance->i_gameLogic->GetGameConfiguration()->turnManager->GetCurrentPlayer().ptr->GetPlayerMoveType()));
                currentPlayerText.Draw();
                turnText.Draw();
            }
            else if (instance->i_gameLogic->GetGameState() == GENERICS::GameState::GameOver)
            {
                if (instance->i_gameLogic->GetGameOverType() == GENERICS::GameOverType::Win)
                {
                    restartButton.isEnabled = true;
                    changeGridButton.isEnabled = true;
                    // changeTurnOrderButton.isEnabled = true;

                    winnerText.SetText("Winner: " + instance->i_gameLogic->GetWinner()->GetPlayerName() + " (" + GENERICS::MoveTypeEnumToString(instance->i_gameLogic->GetWinner()->GetPlayerMoveType()) + ")");
                    gameOverText.Draw();
                    winnerText.Draw();
                    restartButton.Draw();
                    changeGridButton.Draw();
                    // changeTurnOrderButton.Draw();
                }
                else if (instance->i_gameLogic->GetGameOverType() == GENERICS::GameOverType::Draw)
                {
                    restartButton.isEnabled = true;
                    changeGridButton.isEnabled = true;
                    // changeTurnOrderButton.isEnabled = true;

                    drawText.Draw();
                    restartButton.Draw();
                    changeGridButton.Draw();
                    // changeTurnOrderButton.Draw();
                }
            }

            EndDrawing();
        }

        CloseWindow();
    }
}
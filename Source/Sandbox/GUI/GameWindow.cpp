#include "GameWindow.h"

#include <durlib.h>
#include <ogrid.h>
#include <ogrid_gui.h>

namespace Sandbox
{
    template class Sandbox::GameWindow<OGRID::TicTacToe>;
    template class Sandbox::GameWindow<OGRID::ConnectFour>;

    template <class T>
    GameWindow<T>::~GameWindow()
    {
        delete m_Game;
    }

    template <class T>
    void GameWindow<T>::Start()
    {
        m_Game = new T();
        m_Running = true;
        m_Game->Initialize();
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(m_Game->m_guiInfo.width,
                   m_Game->m_guiInfo.height,
                   m_Game->m_guiInfo.windowName.c_str());
        SetTargetFPS(m_Game->m_guiInfo.targetFPS);
        Run();
    }

    template <class T>
    void GameWindow<T>::OnUpdate()
    {
        if (WindowShouldClose())
        {
            m_Running = false;
            return;
        }
        UpdateWindowDimensions();
        // Update
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && m_Game->GetGameState() != OGRID::GameState::GameOver)
        {
            MouseButtonPress();
        }

        restartButton->Update();
        // changeGridButton.Update();
        // changeTurnOrderButton.Update();

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (m_Game->GetGameState() == OGRID::GameState::InProgress)
        {
            InProgress();
        }
        else if (m_Game->GetGameState() == OGRID::GameState::GameOver)
        {
            GameOver();
        }

        EndDrawing();
    }

    template <class T>
    void GameWindow<T>::PreRun()
    {
        m_Game->SetupGame();
        m_Game->StartGame();

        restartButton = new OGRID::Button(
            {static_cast<float>(m_Game->m_guiInfo.width) / 2 - 100,
             static_cast<float>(m_Game->m_guiInfo.height) / 2 + 30, 200, 40},
            GRAY, DARKGRAY, LIGHTGRAY, [this]()
            {
                    CLI_TRACE("Restarting game...");
                    m_Game->ResetGame();
                    m_Game->SetGameState(OGRID::GameState::InProgress); },
            "Restart", false);

        // OGRID::Button changeGridButton(
        //         {static_cast<float>(m_Game.m_guiInfo->width) / 2 - 100,
        //          static_cast<float>(m_Game.m_guiInfo->height) / 2 + 90, 200, 40},
        //         GRAY, DARKGRAY, LIGHTGRAY, []()
        //         {
        //             CLI_TRACE("Changing Grid Layout");
        //             instance->ChangeGridLayout();
        //
        //             instance->i_gameLogic->ResetGame();
        //             instance->i_gameLogic->SetGameState(OGRID::GameState::InProgress); },
        //         "Change Grid", false);

        gameOverText = new OGRID::Text("Game Over!", 20, 0, 100, BLACK, OGRID::Justify::CENTER_X, m_Game->m_guiInfo.width, m_Game->m_guiInfo.height);

        winnerText = new OGRID::Text("Winner: ", 20, 0, 150, BLACK, OGRID::Justify::CENTER_X, m_Game->m_guiInfo.width, m_Game->m_guiInfo.height);

        currentPlayerText = new OGRID::Text("Current Player: ", 8, 5, 5, BLACK, OGRID::Justify::NONE, m_Game->m_guiInfo.width, m_Game->m_guiInfo.height);
        turnText = new OGRID::Text("Turn: ", 8, 5, 20, BLACK, OGRID::Justify::NONE, m_Game->m_guiInfo.width, m_Game->m_guiInfo.height);

        drawText = new OGRID::Text("Draw!", 20, 0, 100, BLACK, OGRID::Justify::CENTER_X, m_Game->m_guiInfo.width, m_Game->m_guiInfo.height);
    }

    template <class T>
    void GameWindow<T>::Run()
    {
        PreRun();
        while (m_Running)
        {
            OnUpdate();
        }
        CloseWindow();
    }

    template <class T>
    void GameWindow<T>::DrawGrid()
    {
        // Set the desired padding around the grid
        float padding = m_Game->m_guiInfo.margin;

        // Calculate the size of the cells to fit the grid in the window, accounting for padding
        m_Game->m_guiInfo.cellSize = (std::min(m_Game->m_guiInfo.width, m_Game->m_guiInfo.height) - (2 * padding)) / static_cast<float>((m_Game->GetGrid()->GetCols() + m_Game->GetGrid()->GetRows() / 20.0f));

        // Calculate any necessary offsets if the window is not square
        float xOffset = (m_Game->m_guiInfo.width - (m_Game->m_guiInfo.cellSize * m_Game->GetGrid()->GetCols())) / 2.0f;
        float yOffset = (m_Game->m_guiInfo.height - (m_Game->m_guiInfo.cellSize * m_Game->GetGrid()->GetRows())) / 2.0f;

        // Adjust offsets for padding
        xOffset = std::max(xOffset, padding);
        yOffset = std::max(yOffset, padding);

        // Draw vertical lines
        for (int i = 0; i <= m_Game->GetGameConfiguration()->grid->GetCols(); i++)
        {
            float lineX = xOffset + i * m_Game->m_guiInfo.cellSize;
            DrawLine(lineX, yOffset, lineX, yOffset + m_Game->m_guiInfo.cellSize * m_Game->GetGrid()->GetRows(), GRAY);
        }

        // Draw horizontal lines
        for (int i = 0; i <= m_Game->GetGameConfiguration()->grid->GetRows(); i++)
        {
            float lineY = yOffset + i * m_Game->m_guiInfo.cellSize;
            DrawLine(xOffset, lineY, xOffset + m_Game->m_guiInfo.cellSize * m_Game->GetGrid()->GetCols(), lineY, GRAY);
        }

        m_Game->OnGUIUpdateGrid();

        m_Game->OnGUIUpdateGridHover(GetCellFromMouse(GetMousePosition()));
    }

    template <class T>
    Vector2 GameWindow<T>::GetCellFromMouse(Vector2 mousePosition)
    {
        // Calculate the starting point of the grid on the screen
        float gridStartX = (m_Game->m_guiInfo.width - (m_Game->m_guiInfo.cellSize * m_Game->GetGrid()->GetCols())) / 2.0f;

        float gridStartY = (m_Game->m_guiInfo.height - (m_Game->m_guiInfo.cellSize * m_Game->GetGrid()->GetRows())) / 2.0f;

        // Adjust the mouse position by subtracting the starting point of the grid
        float adjustedMouseX = mousePosition.x - gridStartX;
        float adjustedMouseY = mousePosition.y - gridStartY;

        // Check if the adjusted mouse position is outside the bounds of the grid
        if (adjustedMouseX < 0 || adjustedMouseY < 0 || adjustedMouseX >= (m_Game->m_guiInfo.cellSize * m_Game->GetGrid()->GetCols()) || adjustedMouseY >= (m_Game->m_guiInfo.cellSize * m_Game->GetGrid()->GetRows()))
        {
            // Outside of grid bounds, return an invalid cell position
            return Vector2(-1, -1);
        }

        // Convert the adjusted mouse position to cell indices
        int cellIndexX = static_cast<int>(adjustedMouseX / m_Game->m_guiInfo.cellSize);
        int cellIndexY = static_cast<int>(adjustedMouseY / m_Game->m_guiInfo.cellSize);

        // The Y coordinate needs to be inverted because the 2D array (0,0) starts at the top-left
        // but in screen coordinates, Y increases as you go down.
        // Since we are not using an upside-down grid, we don't invert Y.

        return Vector2(static_cast<float>(cellIndexX), static_cast<float>(cellIndexY));
    }

    template <class T>
    void GameWindow<T>::UpdateWindowDimensions()
    {
        m_Game->m_guiInfo.width = GetScreenWidth();
        m_Game->m_guiInfo.height = GetScreenHeight();
    }

    template <class T>
    void GameWindow<T>::MouseButtonPress()
    {
        Vector2 cell = GetCellFromMouse(GetMousePosition());

        try
        {
            if (cell.x == -1 || cell.y == -1)
                throw std::runtime_error("Invalid cell position.");
            else
                m_Game->MakeMove((unsigned char)cell.y, (unsigned char)cell.x);
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

    template <class T>
    void GameWindow<T>::GameOver()
    {
        if (m_Game->GetGameOverType() == OGRID::GameOverType::Win)
        {
            restartButton->isEnabled = true;
            // changeGridButton.isEnabled = true;
            // changeTurnOrderButton.isEnabled = true;

            winnerText->SetText("Winner: " + m_Game->GetWinner()->GetPlayerName() + " (" + OGRID::MoveTypeEnumToString(m_Game->GetWinner()->GetPlayerMoveType()) + ")");
            gameOverText->Draw();
            winnerText->Draw();
            restartButton->Draw();
            // changeGridButton.Draw();
            // changeTurnOrderButton.Draw();
        }
        else if (m_Game->GetGameOverType() == OGRID::GameOverType::Draw)
        {
            restartButton->isEnabled = true;
            // changeGridButton.isEnabled = true;
            // changeTurnOrderButton.isEnabled = true;

            drawText->Draw();
            restartButton->Draw();
            // changeGridButton.Draw();
            // changeTurnOrderButton.Draw();
        }
    }

    template <class T>
    void GameWindow<T>::InProgress()
    {
        restartButton->isEnabled = false;
        // changeGridButton.isEnabled = false;
        // changeTurnOrderButton.isEnabled = false;

        DrawGrid();
        currentPlayerText->SetText("Current Player: " + m_Game->GetCurrentPlayer().ptr->GetPlayerName());
        turnText->SetText("Turn: " + OGRID::MoveTypeEnumToString(m_Game->GetCurrentPlayer().ptr->GetPlayerMoveType()));
        currentPlayerText->Draw();
        turnText->Draw();
    }
}
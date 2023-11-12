#pragma once

#include <GUI/iGUI.h>
#include <GameLogic/GameConfiguration.h>

struct Vector2;

namespace OGRIDSandbox
{
    // Forward declarations
    class TicTacToeLogic;

    class TicTacToeGUI : OGRID::iGUI
    {
    private:
        static TicTacToeLogic *i_gameLogic;
        static bool i_randomizeFirstPlayer;

    public:
        // Getters & Setters
        ~TicTacToeGUI();

        TicTacToeGUI();

    public:
        static TicTacToeLogic *GetGameLogic();

        static void SetGameConfiguration(OGRID::GameConfiguration *gameConfiguration);

        static void SetRandomizeFirstPlayer(bool randomizeFirstPlayer);

        // Private methods
    private:
        static void DrawGrid();

        static Vector2 GetCellFromMouse(Vector2 mousePosition);

        void DrawX(int row, int col);
        void DrawO(int row, int col);

        void ChangeGridLayout();

        void ChangeTurnOrder();

        // Public methods
    public:
        void InitializeWindow(std::string windowName, int screenWidth, int screenHeight, int targetFPS) override;
        void BeginMainLoop() override;
    };
}
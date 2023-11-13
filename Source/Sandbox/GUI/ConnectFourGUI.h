#pragma once

#include <GUI/iGUI.h>
#include <GameLogic/GameConfiguration.h>

struct Vector2;

namespace OGRIDSandbox{
    class ConnectFourLogic;

    class ConnectFourGUI : OGRID::iGUI{
    private:
        static ConnectFourLogic *i_gameLogic;
        static bool i_randomizeFirstPlayer;

        // Variables for alpha of circles
        float alpha = 1.0f;
        float alphaSpeed = 0.025f;  // Speed of the transition

    public:
        // Getters & Setters
        ~ConnectFourGUI();

        ConnectFourGUI();

    public:
        static ConnectFourLogic *GetGameLogic();

        static void SetGameConfiguration(OGRID::GameConfiguration *gameConfiguration);

        static void SetRandomizeFirstPlayer(bool randomizeFirstPlayer);

        // Private methods
    private:
        static void DrawGrid();

        static Vector2 GetCellFromMouse(Vector2 mousePosition);

        void DrawRED(int row, int col);
        void DrawBLACK(int row, int col);

        void DrawREDBlinking(int row, int col);
        void DrawBLACKBlinking(int row, int col);

        void ChangeTurnOrder();

        // Public methods
    public:
        void InitializeWindow(std::string windowName, int screenWidth, int screenHeight, int targetFPS) override;
        void BeginMainLoop() override;
    };
}

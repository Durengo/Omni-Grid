// #pragma once

// #include <raylib.h>

// namespace OGRID
// {
//     class Button;
//     class Text;
// }

// namespace Sandbox
// {
//     template <class T>
//     class GameWindow
//     {
//     private:
//         T *m_Game;
//         bool m_Running = false;
//         OGRID::Button *restartButton;
//         OGRID::Text *gameOverText;
//         OGRID::Text *winnerText;
//         OGRID::Text *currentPlayerText;
//         OGRID::Text *turnText;
//         OGRID::Text *drawText;

//     public:
//         GameWindow() = default;
//         ~GameWindow();

//         void Start();

//     private:
//         void Run();

//         void PreRun();

//         void OnUpdate();

//         void DrawGrid();

//         Vector2 GetCellFromMouse(Vector2 mousePosition);

//         void UpdateWindowDimensions();

//         void MouseButtonPress();

//         void InProgress();

//         void GameOver();
//     };
// }

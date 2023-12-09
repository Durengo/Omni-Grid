#pragma once

#include <raylib.h>

/**
 * @file GameWindow.h
 * @brief Game window
 * @date 2023-12-06
 * @see https://www.raylib.com/
 */

namespace OGRID
{
    class Button;
    class Text;
}

namespace OGRID
{
    // Forward declaration
    class User;
}
namespace Sandbox
{

    /**
     * @brief Game window
     * @details Servers as a wrapper around raylib.
     * @date 2023-12-06
     * @tparam T Game logic, must inherit from IGame.
     * @see https://www.raylib.com/
     * @see IGame
     */
    template <class T>
    class GameWindow
    {
    private:
        /**
         * @brief Game logic.
         * @date 2023-12-06
         * @see IGame
         */
        T *m_Game;

        /**
         * @brief Is the game running.
         * @date 2023-12-06
         */
        bool m_Running = false;

        /**
         * @brief Restart button.
         * @date 2023-12-06
         * @see Button
         */
        OGRID::Button *restartButton;

        /**
         * @brief Game over text.
         * @date 2023-12-06
         * @see Text
         */
        OGRID::Text *gameOverText;

        /**
         * @brief Winner text.
         * @date 2023-12-06
         * @see Text
         */
        OGRID::Text *winnerText;

        /**
         * @brief Current player text.
         * @date 2023-12-06
         * @see Text
         */
        OGRID::Text *currentPlayerText;

        /**
         * @brief Turn text.
         * @date 2023-12-06
         * @see Text
         */
        OGRID::Text *turnText;

        /**
         * @brief Draw text.
         * @date 2023-12-06
         * @see Text
         */
        OGRID::Text *drawText;

    public:
        /**
         * @brief Construct a new GameWindow object.
         * @date 2023-12-06
         */
        GameWindow() = default;

        /**
         * @brief Destroy the GameWindow object.
         * @date 2023-12-06
         */
        ~GameWindow();

        /**
         * @brief Start the game.
         * @details Serves as an entry point for the game.
         * @date 2023-12-06
         * @param user User object.
         * @see User
         */
        void Start(OGRID::User *user);

    private:
        /**
         * @brief Run the game.
         * @date 2023-12-06
         */
        void Run();

        /**
         * @brief Run checks before the game starts.
         * @date 2023-12-06
         */
        void PreRun();

        /**
         * @brief Update the game.
         * @date 2023-12-06
         */
        void OnUpdate();

        /**
         * @brief Draw the game.
         * @date 2023-12-06
         */
        void DrawGrid();

        /**
         * @brief Get the cell from mouse position.
         * @date 2023-12-06
         * @param mousePosition Mouse position.
         * @return Vector2 Cell position
         */
        Vector2 GetCellFromMouse(Vector2 mousePosition);

        /**
         * @brief Update the window dimensions.
         * @date 2023-12-06
         */
        void UpdateWindowDimensions();

        /**
         * @brief Called when the mouse button is pressed.
         * @date 2023-12-06
         */
        void MouseButtonPress();

        /**
         * @brief Turns off logic while the game is in progress.
         * @details Example: Restart button is disabled while the game is in progress.
         * @date 2023-12-06
         */
        void InProgress();

        /**
         * @brief Turns on logic while the game is not in progress.
         * @details Example: Restart button is enabled while the game is not in progress.
         * @date 2023-12-06
         */
        void GameOver();
    };
}

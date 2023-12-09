#pragma once

#include "GameLogicInterface/IGame.h"
#include "User/User.h"

/**
 * @file TicTacToe.h
 * @brief TicTacToe game logic
 * @date 2023-12-06
 * @see https://en.wikipedia.org/wiki/Tic-tac-toe
 */

namespace OGRID
{
    /**
     * @brief TicTacToe game logic
     * @date 2023-12-06
     */
    class TicTacToe : public IGame
    {
    public:
        /**
         * @brief Construct a new TicTacToe object
         * @date 2023-12-06
         */
        TicTacToe() = default;

        /**
         * @brief Destroy the TicTacToe object
         * @date 2023-12-06
         */
        ~TicTacToe() = default;

        /**
         * @brief Try to make a move
         * @date 2023-12-06
         * @param row Row of the cell
         * @param col Column of the cell
         * @return true If the move was successful, false otherwise
         */
        bool TryMakeMove(unsigned char &row, unsigned char &col) override;

        /**
         * @brief Check if the game has a winning condition
         * @date 2023-12-06
         * @return true If the game has a winning condition, false otherwise
         */
        bool IsWinningCondition() override;

        /**
         * @brief Check if the game has a draw condition
         * @date 2023-12-06
         * @return true If the game has a draw condition, false otherwise
         */
        bool IsDrawCondition() override;
        // bool IsWinningCondition(unsigned char row, unsigned char col) override;
        // bool IsWinningCondition(char playerChar) override;
        // bool IsDrawCondition(unsigned char row, unsigned char col) override;
        // void SetupPlayers(const std::vector<int> &totalValidSides) override;

        /**
         * @brief Setup the players
         * @date 2023-12-06
         */
        void SetupPlayers() override;

        /**
         * @brief Initialize the game
         * @date 2023-12-06
         */
        void Initialize(OGRID::User* user) override;

        /**
         * @brief Update the grid on the GUI
         * @date 2023-12-06
         */
        void OnGUIUpdateGrid() override;

        /**
         * @brief Update the grid on the GUI when hovering
         * @date 2023-12-06
         * @param cell The cell that is being hovered
         */
        void OnGUIUpdateGridHover(Vector2 cell) override;

    private:
        /**
         * @brief Draw an X on the grid
         * @date 2023-12-06
         * @param row Row of the cell
         * @param col Column of the cell
         */
        void DrawX(int row, int col);

        /**
         * @brief Draw an O on the grid
         * @date 2023-12-06
         * @param row Row of the cell
         * @param col Column of the cell
         */
        void DrawO(int row, int col);
    };
}
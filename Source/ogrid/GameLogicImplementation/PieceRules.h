#pragma once

#include "GameLogicInterface/IMoveRule.h"
#include "Player/Piece.h"

/**
 * @file PieceRules.h
 * @brief Contains the PieceRules class
 * @date 2023-12-06
 */

namespace OGRID
{

    /**
     * @brief The PieceRules class. Used to represent the rules of a piece.
     * @details It contains the move rules of the piece and the attack rules of the piece.
     * @date 2023-12-06
     */
    class SimplePlaceMoveRule : public IMoveRule
    {
    public:
        /**
         * @brief Check if the move is valid.
         * @details Check if the move is valid. It is valid if the end cell is unoccupied.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param fromX The x coordinate of the start cell.
         * @param fromY The y coordinate of the start cell.
         * @param toX The x coordinate of the end cell.
         * @param toY The y coordinate of the end cell.
         * @return True if the move is valid, false otherwise.
         * @note This is a simple move rule. It is used for games like tic tac toe.
         */
        // We only need to check if the end cell is unoccupied, as there is no concept of a "start" cell in tic tac toe.
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override;
    };

    /**
     * @brief The PieceRules class. Used to represent the rules of a piece.
     * @details It contains the move rules of the piece and the attack rules of the piece.
     * @date 2023-12-06
     */
    class NormalCheckersMoveRule : public IMoveRule
    {
    public:
        /**
         * @brief Check if the move is valid.
         * @details Check if the move is valid. It is valid if the end cell is unoccupied.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param fromX The x coordinate of the start cell.
         * @param fromY The y coordinate of the start cell.
         * @param toX The x coordinate of the end cell.
         * @param toY The y coordinate of the end cell.
         * @return True if the move is valid, false otherwise.
         * @note This specifically checks the starting cell and the ending cell.
         * @note This is specifically used for Checkers.
         */
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override;
    };

    /**
     * @brief The PieceRules class. Used to represent the rules of a piece.
     * @details It contains the move rules of the piece and the attack rules of the piece.
     * @date 2023-12-06
     */
    class JumpNormalCheckersAttackRule : public IAttackRule
    {
    public:
        /**
         * @brief Check if the attack is valid.
         * @details Check if the attack is valid. It is valid if the end cell is unoccupied.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param fromX The x coordinate of the start cell.
         * @param fromY The y coordinate of the start cell.
         * @param toX The x coordinate of the end cell.
         * @param toY The y coordinate of the end cell.
         * @param canContinue A boolean value that indicates if the attack can continue.
         * @return True if the attack is valid, false otherwise.
         * @note This specifically checks the starting cell and the ending cell.
         * @note This is specifically used for Checkers.
         */
        bool IsValidAttack(Grid *grid, int fromX, int fromY, int toX, int toY, bool &canContinue) const override;
    };

    /**
     * @brief The PieceRules class. Used to represent the rules of a piece.
     * @details It contains the move rules of the piece and the attack rules of the piece.
     * @date 2023-12-06
     */
    class SuperCheckersMoveRule : public IMoveRule
    {
    public:
        /**
         * @brief Check if the move is valid.
         * @details Check if the move is valid. It is valid if the end cell is unoccupied.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param fromX The x coordinate of the start cell.
         * @param fromY The y coordinate of the start cell.
         * @param toX The x coordinate of the end cell.
         * @param toY The y coordinate of the end cell.
         * @return True if the move is valid, false otherwise.
         * @note This specifically checks the starting cell and the ending cell.
         * @note This is specifically used for Super Checkers.
         * @note This is used for the Super Checkers piece.
         */
        bool IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const override;
    };

    /**
     * @brief The PieceRules class. Used to represent the rules of a piece.
     * @details It contains the move rules of the piece and the attack rules of the piece.
     * @date 2023-12-06
     */
    class JumpSuperCheckersAttackRule : public IAttackRule
    {
    public:
        /**
         * @brief Check if the attack is valid.
         * @details Check if the attack is valid. It is valid if the end cell is unoccupied.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param fromX The x coordinate of the start cell.
         * @param fromY The y coordinate of the start cell.
         * @param toX The x coordinate of the end cell.
         * @param toY The y coordinate of the end cell.
         * @param canContinue A boolean value that indicates if the attack can continue.
         * @return True if the attack is valid, false otherwise.
         * @note This specifically checks the starting cell and the ending cell.
         * @note This is specifically used for Super Checkers.
         * @note This is used for the Super Checkers piece.
         */
        bool IsValidAttack(Grid *grid, int fromX, int fromY, int toX, int toY, bool &canContinue) const override;
    };
}
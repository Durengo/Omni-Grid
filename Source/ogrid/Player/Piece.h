#pragma once

#include <string>
#include <vector>

#include <GameLogicInterface/IAttackRule.h>
#include "GameLogicInterface/IMoveRule.h"
#include "Player/Player.h"

/**
 * @file Piece.h
 * @brief Contains the Piece class
 * @date 2023-12-06
 */

namespace OGRID
{
    /**
     * @brief The Piece class. Used to represent a piece.
     * @details It contains the representation of the piece, the move rules of the piece, the attack rules of the piece and the owner of the piece.
     * @date 2023-12-06
     */
    class Piece
    {
    protected:
        /**
         * @brief The representation of the piece.
         * @details The representation of the piece. It is used to identify the piece.
         * @date 2023-12-06
         */
        // String representation of the move (char), like (chess) "K" for king, "Q" for queen, etc.
        std::string m_representation;

        /**
         * @brief The move rules of the piece.
         * @details It is used to check if the move is valid.
         */
        // Rules for this move type
        std::vector<IMoveRule *> m_moveRules;

        /**
         * @brief The attack rules of the piece.
         * @details It is used to check if the attack is valid.
         */
        // Rules for attacking
        std::vector<IAttackRule *> m_attackRules;

        /**
         * @brief The owner of the piece.
         * @details It is used to identify the owner of the piece.
         * @date 2023-12-06
         */
        // Owner of this piece
        Player *m_owner;

    public:
        /**
         * @brief Construct a new Piece object.
         * @details Construct a new Piece object using the representation of the piece and the owner of the piece.
         * @date 2023-12-06
         * @param rep The representation of the piece.
         * @param player The owner of the piece.
         */
        Piece(std::string rep, Player *player);

        /**
         * @brief Destroy the Piece object.
         * @date 2023-12-06
         */
        ~Piece();

        /**
         * @brief Add a move rule to the piece.
         * @details Add a move rule to the piece.
         * @date 2023-12-06
         * @param rule The move rule to add.
         */
        void AddMoveRule(IMoveRule *rule);

        /**
         * @brief Add an attack rule to the piece.
         * @details Add an attack rule to the piece.
         * @date 2023-12-06
         * @param rule The attack rule to add.
         */
        void AddAttackRule(IAttackRule *rule);

        /**
         * @brief Get the representation of the piece.
         * @date 2023-12-06
         * @return The representation of the piece.
         */
        const std::string &GetRepresentation() const;

        /**
         * @brief Get the owner of the piece.
         * @date 2023-12-06
         * @return The owner of the piece.
         */
        const Player *GetOwner() const;

        /**
         * @brief Set the owner of the piece.
         * @date 2023-12-06
         * @param player The owner of the piece.
         */
        void SetOwner(Player *player);

        /**
         * @brief Check if the move is valid.
         * @details Check if the move is valid using the move rules.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param fromX The x coordinate of the start cell.
         * @param fromY The y coordinate of the start cell.
         * @param toX The x coordinate of the end cell.
         * @param toY The y coordinate of the end cell.
         * @return True if the move is valid, false otherwise.
         */
        bool isValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const;

        /**
         * @brief Check if the attack is valid.
         * @details Check if the attack is valid using the attack rules.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param fromX The x coordinate of the start cell.
         * @param fromY The y coordinate of the start cell.
         * @param toX The x coordinate of the end cell.
         * @param toY The y coordinate of the end cell.
         * @param canContinue True if the attack can continue, false otherwise.
         * @return True if the attack is valid, false otherwise.
         */
        bool isValidAttack(Grid *grid, int fromX, int fromY, int toX, int toY, bool &canContinue) const;
    };
}
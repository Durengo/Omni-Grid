#pragma once

#include <string>
#include <typeinfo>

#include "Grid/grid.h"
#include "Player/Piece.h"

/**
 * @file GameStateExtensions.h
 * @brief Contains the GameStateExtensions class
 * @date 2023-12-06
 */

/*
Checking for class type of pieces would look like this:
CheckForRecurringPieceInRow(typeid(XPiece), 3))
*/
namespace OGRID
{
    // Forward declarations
    // class Grid;
    // class Piece;

    /**
     * @brief The GameStateExtensions class. Used to extend the GameStateChecker class.
     * @details It contains the extension methods for the GameStateChecker class.
     * @date 2023-12-06
     */
    class GameStateExtensions
    {
    public:
        /**
         * @brief Check the exact amount of duplicate pieces in a row.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param pieceRepresentation The representation of the piece to be counted.
         * @param dupeCount The exact number of duplicate pieces to be counted.
         * @return True if the exact amount of duplicate pieces are found, false otherwise.
         */
        bool CheckForRecurringStringInRow(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const;
        /**
         * @brief Check the exact amount of duplicate pieces in a row.
         * @details This should be used like this: CheckForRecurringPieceInRow(typeid(XPiece), 3))
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param pieceType The type of the piece to be counted.
         * @param dupeCount The exact number of duplicate pieces to be counted.
         * @return True if the exact amount of duplicate pieces are found, false otherwise.
         */
        bool CheckForRecurringPieceInRow(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const;

        /**
         * @brief Check the exact amount of duplicate pieces in a column.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param pieceRepresentation The representation of the piece to be counted.
         * @param dupeCount The exact number of duplicate pieces to be counted.
         * @return True if the exact amount of duplicate pieces are found, false otherwise.
         */
        bool CheckForRecurringStringInCol(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const;

        /**
         * @brief Check the exact amount of duplicate pieces in a column.
         * @details This should be used like this: CheckForRecurringPieceInCol(typeid(XPiece), 3))
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param pieceType The type of the piece to be counted.
         * @param dupeCount The exact number of duplicate pieces to be counted.
         * @return True if the exact amount of duplicate pieces are found, false otherwise.
         */
        bool CheckForRecurringPieceInCol(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const;

        /**
         * @brief Check the exact amount of duplicate pieces in a diagonal.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param pieceRepresentation The representation of the piece to be counted.
         * @param dupeCount The exact number of duplicate pieces to be counted.
         * @return True if the exact amount of duplicate pieces are found, false otherwise.
         */
        bool CheckForRecurringStringInDiagonal(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const;

        /**
         * @brief Check the exact amount of duplicate pieces in a diagonal.
         * @details This should be used like this: CheckForRecurringPieceInDiagonal(typeid(XPiece), 3))
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param pieceType The type of the piece to be counted.
         * @param dupeCount The exact number of duplicate pieces to be counted.
         * @return True if the exact amount of duplicate pieces are found, false otherwise.
         */
        bool CheckForRecurringPieceInDiagonal(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const;

        /**
         * @brief Check the exact amount of duplicate pieces in an anti-diagonal.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param pieceRepresentation The representation of the piece to be counted.
         * @param dupeCount The exact number of duplicate pieces to be counted.
         * @return True if the exact amount of duplicate pieces are found, false otherwise.
         */
        bool CheckForRecurringStringInAntiDiagonal(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const;

        /**
         * @brief Check the exact amount of duplicate pieces in an anti-diagonal.
         * @details This should be used like this: CheckForRecurringPieceInAntiDiagonal(typeid(XPiece), 3))
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @param pieceType The type of the piece to be counted.
         * @param dupeCount The exact number of duplicate pieces to be counted.
         * @return True if the exact amount of duplicate pieces are found, false otherwise.
         */
        bool CheckForRecurringPieceInAntiDiagonal(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const;

        /**
         * @brief Check if all the spots in the grid are filled.
         * @date 2023-12-06
         * @param grid The grid of the game.
         * @return True if all the spots in the grid are filled, false otherwise.
         */
        bool CheckIfAllSpotsFilled(Grid *grid) const;
    };
}
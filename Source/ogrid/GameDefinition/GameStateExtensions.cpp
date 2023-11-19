#include "GameStateExtensions.h"

namespace OGRID
{
    bool GameStateExtensions::CheckForRecurringStringInRow(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const
    {
        for (unsigned char row = 0; row < grid->GetRows(); ++row)
        {
            size_t count = 0;
            for (unsigned char col = 0; col < grid->GetCols(); ++col)
            {
                Piece *piece = grid->GetPieceAt(row, col);
                if (piece == nullptr)
                {
                    count = 0;
                    continue;
                }
                if (piece->GetRepresentation() == pieceRepresentation)
                {
                    if (++count >= dupeCount)
                        return true;
                }
                else
                {
                    count = 0;
                }
            }
        }
        return false;
    }

    bool GameStateExtensions::CheckForRecurringPieceInRow(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const
    {
        for (unsigned char row = 0; row < grid->GetRows(); ++row)
        {
            size_t count = 0;
            for (unsigned char col = 0; col < grid->GetCols(); ++col)
            {
                Piece *piece = grid->GetPieceAt(row, col);
                if (piece == nullptr)
                {
                    count = 0;
                    continue;
                }
                if (typeid(*piece) == pieceType)
                {
                    if (++count >= dupeCount)
                        return true;
                }
                else
                {
                    count = 0;
                }
            }
        }
        return false;
    }

    bool GameStateExtensions::CheckForRecurringStringInCol(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const
    {
        for (unsigned char col = 0; col < grid->GetCols(); ++col)
        {
            unsigned char count = 0;
            for (unsigned char row = 0; row < grid->GetRows(); ++row)
            {
                Piece *piece = grid->GetPieceAt(row, col);
                if (piece == nullptr)
                {
                    count = 0;
                    continue;
                }
                if (piece->GetRepresentation() == pieceRepresentation)
                {
                    if (++count >= dupeCount)
                        return true;
                }
                else
                {
                    count = 0;
                }
            }
        }
        return false;
    }

    bool GameStateExtensions::CheckForRecurringPieceInCol(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const
    {
        for (unsigned char col = 0; col < grid->GetCols(); ++col)
        {
            unsigned char count = 0;
            for (unsigned char row = 0; row < grid->GetRows(); ++row)
            {
                Piece *piece = grid->GetPieceAt(row, col);
                if (piece == nullptr)
                {
                    count = 0;
                    continue;
                }
                if (typeid(*piece) == pieceType)
                {
                    if (++count >= dupeCount)
                        return true;
                }
                else
                {
                    count = 0;
                }
            }
        }
        return false;
    }

    bool GameStateExtensions::CheckForRecurringStringInDiagonal(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const
    {
        // Check from top-left to bottom-right
        for (unsigned char row = 0; row <= grid->GetRows() - 3; ++row)
        {
            for (unsigned char col = 0; col <= grid->GetCols() - 3; ++col)
            {
                unsigned char count = 0;
                for (unsigned char i = 0; i + row < grid->GetRows() && i + col < grid->GetCols(); ++i)
                {
                    // TODO: This will cause problems when going out of bounds of the grid
                    Piece *piece = grid->GetPieceAt(row + i, col + i);
                    if (piece == nullptr)
                    {
                        count = 0;
                        continue;
                    }
                    if (piece->GetRepresentation() == pieceRepresentation)
                    {
                        if (++count >= dupeCount)
                            return true;
                    }
                    else
                    {
                        // Exit the diagonal check if a different string is found
                        break;
                    }
                }
            }
        }
        return false;
    }

    bool GameStateExtensions::CheckForRecurringPieceInDiagonal(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const
    {
        // Check from top-left to bottom-right
        for (unsigned char row = 0; row <= grid->GetRows() - 3; ++row)
        {
            for (unsigned char col = 0; col <= grid->GetCols() - 3; ++col)
            {
                unsigned char count = 0;
                for (unsigned char i = 0; i + row < grid->GetRows() && i + col < grid->GetCols(); ++i)
                {
                    // TODO: This will cause problems when going out of bounds of the grid
                    Piece *piece = grid->GetPieceAt(row + i, col + i);
                    if (piece == nullptr)
                    {
                        count = 0;
                        continue;
                    }
                    if (typeid(*piece) == pieceType)
                    {
                        if (++count >= dupeCount)
                            return true;
                    }
                    else
                    {
                        // Exit the diagonal check if a different piece is found
                        break;
                    }
                }
            }
        }
        return false;
    }

    bool GameStateExtensions::CheckForRecurringStringInAntiDiagonal(Grid *grid, const std::string &pieceRepresentation, unsigned char dupeCount) const
    {
        // Check from top-right to bottom-left
        for (unsigned char row = 0; row <= grid->GetRows() - 3; ++row)
        {
            for (unsigned char col = grid->GetCols() - 1; col >= 2; --col)
            {
                unsigned char count = 0;
                for (unsigned char i = 0; i + row < grid->GetRows() && col - i >= 0; ++i)
                {
                    Piece *piece = grid->GetPieceAt(row + i, col - i);
                    if (piece == nullptr)
                    {
                        count = 0;
                        continue;
                    }
                    if (piece->GetRepresentation() == pieceRepresentation)
                    {
                        if (++count >= dupeCount)
                            return true;
                    }
                    else
                    {
                        // Exit the anti-diagonal check if a different string is found
                        break;
                    }
                }
            }
        }
        return false;
    }

    bool GameStateExtensions::CheckForRecurringPieceInAntiDiagonal(Grid *grid, const std::type_info &pieceType, unsigned char dupeCount) const
    {
        // Check from top-right to bottom-left
        for (unsigned char row = 0; row <= grid->GetRows() - 3; ++row)
        {
            for (unsigned char col = grid->GetCols() - 1; col >= 2; --col)
            {
                unsigned char count = 0;
                for (unsigned char i = 0; i + row < grid->GetRows() && col - i >= 0; ++i)
                {
                    Piece *piece = grid->GetPieceAt(row + i, col - i);
                    if (piece == nullptr)
                    {
                        count = 0;
                        continue;
                    }
                    if (typeid(*piece) == pieceType)
                    {
                        if (++count >= dupeCount)
                            return true;
                    }
                    else
                    {
                        // Exit the anti-diagonal check if a different piece is found
                        break;
                    }
                }
            }
        }
        return false;
    }

    bool GameStateExtensions::CheckIfAllSpotsFilled(Grid *grid) const
    {
        // Check if all spots are filled.
        for (int i = 0; i < grid->GetRows(); ++i)
        {
            for (int j = 0; j < grid->GetCols(); ++j)
            {
                Piece *piece = grid->GetPieceAt(i, j);
                if (piece == nullptr)
                {
                    // Found an empty spot, so not all spots are filled.
                    return false;
                }
            }
        }
        return true;
    }
}
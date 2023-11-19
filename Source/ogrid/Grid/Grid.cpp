#include "Grid.h"

#include <stdexcept>

#include "fmt/format.h"

#include "GameDefinition/Piece.h"

namespace OGRID
{
    // TODO: Resize works properly when the grid is a square matrix. This will most likely break things when the grid is a rectangle.
    // Constructors & Destructors
    Grid::Grid(unsigned char rows, unsigned char cols, Piece *defaultPiece)
        : rows(rows), cols(cols), defaultPiece(defaultPiece)
    {
        this->grid.resize(rows);

        for (unsigned char i = 0; i < rows; ++i)
        {
            this->grid[i].resize(cols);
            for (unsigned char j = 0; j < cols; ++j)
            {
                // Allocate a new Cell
                this->grid[i][j] = new Cell();
                // Set the default piece
                this->grid[i][j]->m_Piece = defaultPiece;
                this->grid[i][j]->m_Row = i;
                this->grid[i][j]->m_Col = j;
            }
        }
    }

    Grid::~Grid()
    {
    }

    // Getters & Setters

    unsigned char Grid::GetRows() const
    {
        return rows;
    }

    void Grid::SetRows(unsigned char rows)
    {
        this->rows = rows;
    }

    unsigned char Grid::GetCols() const
    {
        return cols;
    }

    void Grid::SetCols(unsigned char cols)
    {
        this->cols = cols;
    }

    const std::vector<std::vector<Cell *>> &Grid::GetGrid() const
    {
        return grid;
    }

    void Grid::SetGrid(const std::vector<std::vector<Cell *>> &newGrid)
    {
        // Not sure if this is necessary.
        if (newGrid.empty() || newGrid[0].empty())
        {
            throw std::invalid_argument("New grid cannot be empty");
        }

        rows = static_cast<unsigned char>(newGrid.size());
        cols = static_cast<unsigned char>(newGrid[0].size());

        grid = newGrid;
    }

    Piece *Grid::GetDefaultPiece() const
    {
        return defaultPiece;
    }

    void Grid::SetDefaultPiece(Piece *defaultPiece)
    {
        this->defaultPiece = defaultPiece;
    }

    Piece *Grid::GetPieceAt(unsigned char row, unsigned char col) const
    {
        return grid[row][col]->m_Piece;
    }

    void Grid::SetPieceAt(unsigned char row, unsigned char col, Piece *piece)
    {
        if (row < 0 || row >= this->GetRows() || col < 0 || col >= this->GetCols())
        {
            throw std::out_of_range("Index out of bounds");
        }
        lastChangedChar[0] = row;
        lastChangedChar[1] = col;
        grid[row][col]->m_Piece = piece;
    }

    Cell *Grid::GetCellAt(unsigned char row, unsigned char col) const
    {
        return grid[row][col];
    }

    void Grid::SetCellAt(unsigned char row, unsigned char col, Cell *cell)
    {
        if (row < 0 || row >= this->GetRows() || col < 0 || col >= this->GetCols())
        {
            throw std::out_of_range("Index out of bounds");
        }
        lastChangedChar[0] = row;
        lastChangedChar[1] = col;
        grid[row][col] = cell;
    }

    void Grid::SetCellAt(unsigned char row, unsigned char col, Piece *piece)
    {
        if (row < 0 || row >= this->GetRows() || col < 0 || col >= this->GetCols())
        {
            throw std::out_of_range("Index out of bounds");
        }
        lastChangedChar[0] = row;
        lastChangedChar[1] = col;

        grid[row][col] = new Cell{piece, row, col};
    }

    std::pair<unsigned char, unsigned char> Grid::GetLastChangedChar() const
    {
        return std::make_pair(lastChangedChar[0], lastChangedChar[1]);
    }

    // Operators

    std::vector<Cell *> &Grid::operator[](size_t index)
    {
        if (index < 0 || index >= this->GetRows())
        {
            throw std::out_of_range("Index out of bounds");
        }
        return grid[index];
    }

    const std::vector<Cell *> &Grid::operator[](size_t index) const
    {
        return grid[index];
    }

    // Public methods
    const std::string Grid::GetGridSize() const
    {
        return fmt::format("{0}x{1}", rows, cols);
    }

    void Grid::ResetGrid()
    {
        for (auto &row : grid)
        {
            for (auto &cell : row)
            {
                if (cell != nullptr)
                {
                    cell->m_Piece = defaultPiece;
                }
            }
        }
        lastChangedChar[0] = 0;
        lastChangedChar[1] = 0;
    }

    void Grid::ResetGridWithNewSize(unsigned char newRows, unsigned char newCols, Piece *defaultPiece)
    {
        rows = newRows;
        cols = newCols;
        defaultPiece = defaultPiece;
        // grid.resize(rows, std::vector<std::string>(cols, defaultPiece));
        this->grid.resize(rows);

        for (unsigned char i = 0; i < rows; ++i)
        {
            this->grid[i].resize(cols);
            for (unsigned char j = 0; j < cols; ++j)
            {
                // Allocate a new Cell
                this->grid[i][j] = new Cell();
                // Set the default piece
                this->grid[i][j]->m_Piece = defaultPiece;
                this->grid[i][j]->m_Row = i;
                this->grid[i][j]->m_Col = j;
            }
        }
        // Don't need this, right?
        // ResetGrid();
    }

    void Grid::ResetGridWithNewDefaultPiece(Piece *defaultPiece)
    {
        defaultPiece = defaultPiece;
        ResetGrid();
    }

    // Previous methods checked for the occurrence of a character in a row, column, diagonal or anti-diagonal.
    // But it checked the whole row, column, diagonal or anti-diagonal.
    // This is incorrect. Because we need to check for at the very least dupCount occurrences of the character in a row.
    // bool Grid::CheckForRecurringStringInRow(const std::string &playerString, unsigned int dupCount)
    // {
    //     for (int row = 0; row < rows; ++row)
    //     {
    //         int count = 0;
    //         for (int col = 0; col < cols; ++col)
    //         {
    //             if (GetStringAt(row, col) == playerString)
    //             {
    //                 if (++count >= dupCount)
    //                     return true;
    //             }
    //             else
    //             {
    //                 count = 0;
    //             }
    //         }
    //     }
    //     return false;
    // }

    // bool Grid::CheckForRecurringStringInCol(const std::string &playerString, unsigned int dupCount)
    // {
    //     for (int col = 0; col < cols; ++col)
    //     {
    //         int count = 0;
    //         for (int row = 0; row < rows; ++row)
    //         {
    //             if (GetStringAt(row, col) == playerString)
    //             {
    //                 if (++count >= dupCount)
    //                     return true;
    //             }
    //             else
    //             {
    //                 count = 0;
    //             }
    //         }
    //     }
    //     return false;
    // }

    // bool Grid::CheckForRecurringStringInDiagonal(const std::string &playerString, unsigned int dupCount)
    // {
    //     // Check from top-left to bottom-right
    //     for (int row = 0; row <= rows - 3; ++row)
    //     {
    //         for (int col = 0; col <= cols - 3; ++col)
    //         {
    //             int count = 0;
    //             for (int i = 0; i + row < rows && i + col < cols; ++i)
    //             {
    //                 if (GetStringAt(row + i, col + i) == playerString)
    //                 {
    //                     if (++count >= dupCount)
    //                         return true;
    //                 }
    //                 else
    //                 {
    //                     // Exit the diagonal check if a different string is found
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    //     return false;
    // }

    // bool Grid::CheckForRecurringStringInAntiDiagonal(const std::string &playerString, unsigned int dupCount)
    // {
    //     // Check from top-right to bottom-left
    //     for (int row = 0; row <= rows - 3; ++row)
    //     {
    //         for (int col = cols - 1; col >= 2; --col)
    //         {
    //             int count = 0;
    //             for (int i = 0; i + row < rows && col - i >= 0; ++i)
    //             {
    //                 if (GetStringAt(row + i, col - i) == playerString)
    //                 {
    //                     if (++count >= dupCount)
    //                         return true;
    //                 }
    //                 else
    //                 {
    //                     // Exit the anti-diagonal check if a different char is found
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    //     return false;
    // }

    // std::string Grid::GetCharCenterMostElement() const
    // {
    //     unsigned char centerRow = rows / 2;
    //     unsigned char centerCol = cols / 2;

    //     if (rows % 2 == 0)
    //         --centerRow;
    //     if (cols % 2 == 0)
    //         --centerCol;

    //     return GetStringAt(centerRow, centerCol);
    // }

    // std::pair<unsigned char, unsigned char> Grid::GetCenterMostCoords() const
    // {
    //     // The center for both rows and columns in case of odd dimensions.
    //     unsigned char centerRow = rows / 2;
    //     unsigned char centerCol = cols / 2;

    //     // If both dimensions are even, adjust to get the top-left centermost element.
    //     if (rows % 2 == 0)
    //         --centerRow;
    //     if (cols % 2 == 0)
    //         --centerCol;

    //     return std::make_pair(centerRow, centerCol);
    // }
}
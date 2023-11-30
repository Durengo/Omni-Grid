#include "Grid.h"

#include <stdexcept>

#include "fmt/format.h"

#include "Player/Piece.h"

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
                Cell *cell = new Cell();
                cell->m_Piece = defaultPiece;
                cell->m_Row = i;
                cell->m_Col = j;
                this->grid[i][j] = cell;
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
            throw std::invalid_argument("New grid cannot be empty");

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
        if (row < 0 || row >= this->GetRows() || col < 0 || col >= this->GetCols())
            throw std::out_of_range("Index out of bounds");

        return grid[row][col]->m_Piece;
    }

    void Grid::SetPieceAt(unsigned char row, unsigned char col, Piece *piece)
    {
        if (piece == nullptr)
            throw std::invalid_argument("Cell cannot be null");

        if (row < 0 || row >= this->GetRows() || col < 0 || col >= this->GetCols())
            throw std::out_of_range("Index out of bounds");

        lastChangedChar[0] = row;
        lastChangedChar[1] = col;
        grid[row][col]->m_Piece = piece;
    }

    Cell *Grid::GetCellAt(unsigned char row, unsigned char col) const
    {
        if (row < 0 || row >= this->GetRows() || col < 0 || col >= this->GetCols())
            throw std::out_of_range("Index out of bounds");

        return grid[row][col];
    }

    void Grid::SetCellAt(unsigned char row, unsigned char col, Cell *cell)
    {
        if (cell == nullptr)
            throw std::invalid_argument("Cell cannot be null");

        if (row < 0 || row >= this->GetRows() || col < 0 || col >= this->GetCols())
            throw std::out_of_range("Index out of bounds");

        lastChangedChar[0] = row;
        lastChangedChar[1] = col;
        grid[row][col] = cell;
    }

    void Grid::SetCellAt(unsigned char row, unsigned char col, Piece *piece)
    {
        if (piece == nullptr)
            throw std::invalid_argument("Cell cannot be null");

        if (row < 0 || row >= this->GetRows() || col < 0 || col >= this->GetCols())
            throw std::out_of_range("Index out of bounds");

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
            throw std::out_of_range("Index out of bounds");

        return grid[index];
    }

    const std::vector<Cell *> &Grid::operator[](size_t index) const
    {
        if (index < 0 || index >= this->GetRows())
            throw std::out_of_range("Index out of bounds");

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
                    cell->m_Piece = defaultPiece;
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

    std::string Grid::GetGridAsString()
    {
#include <sstream>

        std::ostringstream ss;

        for (unsigned char i = 0; i < rows; ++i)
        {
            for (unsigned char j = 0; j < cols; ++j)
            {
                if (j > 0)
                    ss << "\t";
                Piece *piece = grid[i][j]->m_Piece;

                if (piece == nullptr)
                    ss << "NULL";
                else
                    ss << piece->GetRepresentation();
                    
                ss << " |";
            }
            if (i < rows - 1)
                ss << "\n";
        }

        return ss.str();
    }
}
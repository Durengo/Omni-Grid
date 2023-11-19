#pragma once

#include <string>
#include <vector>

namespace OGRID
{
    class Piece;

    struct Cell
    {
        Piece *m_Piece;
        unsigned char m_Row;
        unsigned char m_Col;
    };

    class Grid
    {
    private:
        // Limit grid size to 255x255.
        unsigned char rows;
        unsigned char cols;
        // Use a 2D array of Cell pointers to represent the grid.
        std::vector<std::vector<Cell *>> grid;

        // Store default Piece for resetting the grid.
        // Important! This will set the whole grid to the same Piece.
        // Careful when setting this to nullptr.
        Piece *defaultPiece;

        // Store which element was last changed.
        unsigned char lastChangedChar[2] = {0, 0};

    public:
        // Constructors & Destructors
        Grid(unsigned char rows, unsigned char cols, Piece *defaultPiece = nullptr);
        ~Grid();

        // Getters & Setters
    public:
        unsigned char GetRows() const;
        void SetRows(unsigned char rows);

        unsigned char GetCols() const;
        void SetCols(unsigned char cols);

        const std::vector<std::vector<Cell *>> &GetGrid() const;
        void SetGrid(const std::vector<std::vector<Cell *>> &newGrid);

        Piece *GetDefaultPiece() const;
        void SetDefaultPiece(Piece *defaultPiece);

        Piece *GetPieceAt(unsigned char row, unsigned char col) const;
        void SetPieceAt(unsigned char row, unsigned char col, Piece *piece);

        Cell *GetCellAt(unsigned char row, unsigned char col) const;
        void SetCellAt(unsigned char row, unsigned char col, Cell *cell);
        void SetCellAt(unsigned char row, unsigned char col, Piece *piece);

        std::pair<unsigned char, unsigned char> GetLastChangedChar() const;

        // Overload the [] operator to access the grid.
    public:
        std::vector<Cell *> &operator[](size_t index);

        const std::vector<Cell *> &operator[](size_t index) const;

        // Public methods
    public:
        const std::string GetGridSize() const;
        void ResetGrid();
        void ResetGridWithNewSize(unsigned char newRows, unsigned char newCols, Piece *defaultPiece = nullptr);
        void ResetGridWithNewDefaultPiece(Piece *defaultPiece = nullptr);

        // bool CheckForRecurringStringInRow(const std::string &playerString, unsigned int dupCount);
        // bool CheckForRecurringStringInCol(const std::string &playerString, unsigned int dupCount);
        // bool CheckForRecurringStringInDiagonal(const std::string &playerString, unsigned int dupCount);
        // bool CheckForRecurringStringInAntiDiagonal(const std::string &playerString, unsigned int dupCount);

        // // This one is broken and should probably be removed...
        // std::string GetCharCenterMostElement() const;
        // std::pair<unsigned char, unsigned char> GetCenterMostCoords() const;
    };
}
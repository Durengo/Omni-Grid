#pragma once

#include <string>
#include <vector>

/**
 * @file Grid.h
 * Test
 * @brief Contains the Grid class.
 * @date 2023-12-06
 */

namespace OGRID
{
    /**
     *
     * @brief The Grid class represents a 2D grid of Cells.
     *
     */
    class Piece;

    /**
     * @brief The Cell struct represents a single cell in the grid.
     * It contains a pointer to a Piece and the row and column of the cell.
     * The Piece pointer can be nullptr if the cell is empty.
     * The row and column are unsigned chars, which means the grid can be at most 255x255.
     * This is more than enough for our purposes.
     * @date 2023-12-06
     * @see Piece
     * @see Grid
     */
    struct Cell
    {
        Piece *m_Piece;
        unsigned char m_Row;
        unsigned char m_Col;
    };

    /**
     * @brief The Grid class represents a 2D grid of Cells.
     * @details The Grid class represents a 2D grid of Cells.
     * It contains the number of rows and columns in the grid, as well as the grid itself.
     * The grid is a 2D array of Cell pointers.
     * The grid can be at most 255x255, which is more than enough for our purposes.
     * The Grid class also contains a default Piece, which is used to reset the grid.
     * @date 2023-12-06
     * @see Piece
     * @see Cell
     * @see Grid
    */
    class Grid
    {
    private:
        /**
         * @brief The number of rows in the grid.
         * @details This is an unsigned char, which means the grid can be at most 255x255.
         * This is more than enough for our purposes.
         * @date 2023-12-06
         */
        unsigned char rows;
        /**
         * @brief The number of columns in the grid.
         * @details This is an unsigned char, which means the grid can be at most 255x255.
         * This is more than enough for our purposes.
         * @date 2023-12-06
         */
        unsigned char cols;
        /**
         * @brief The grid itself.
         * @details This is a 2D array of Cell pointers.
         * @date 2023-12-06
         * @see Cell
         */
        std::vector<std::vector<Cell *>> grid;

        // Store default Piece for resetting the grid.
        // Important! This will set the whole grid to the same Piece.
        // Careful when setting this to nullptr.
        /**
         * @brief The default Piece for the grid.
         * @details This is the Piece that will be used to reset the grid.
         * @date 2023-12-06
         * @see Piece
         */
        Piece *defaultPiece;

        // Store which element was last changed.
        /**
         * @brief The last changed element.
         * @details This is a pair of unsigned chars that stores the row and column of the last changed element.
         * @date 2023-12-06
         */
        unsigned char lastChangedChar[2] = {0, 0};

    public:
        // Constructors & Destructors
        /**
         * @brief Construct a new Grid object.
         * @details This constructor will create a grid with the specified number of rows and columns.
         * It will also set the default Piece to the specified Piece.
         * @date 2023-12-06
         * @param rows The number of rows in the grid.
         * @param cols The number of columns in the grid.
         * @param defaultPiece The default Piece for the grid.
         * @see Piece
         */
        Grid(unsigned char rows, unsigned char cols, Piece *defaultPiece = nullptr);

        /**
         * @brief Destroy the Grid object.
         * @details This destructor will delete all the Cells in the grid.
         * @date 2023-12-06
         */
        ~Grid();

        // Getters & Setters
    public:
        /**
         * @brief Get the number of rows in the grid.
         * @details This is an unsigned char, which means the grid can be at most 255x255.
         * This is more than enough for our purposes.
         * @date 2023-12-06
         * @return The number of rows in the grid.
         */
        unsigned char GetRows() const;
        /**
         * @brief Set the number of rows in the grid.
         * @details This is an unsigned char, which means the grid can be at most 255x255.
         * This is more than enough for our purposes.
         * @date 2023-12-06
         * @param rows The number of rows in the grid.
         */
        void SetRows(unsigned char rows);

        /**
         * @brief Get the number of columns in the grid.
         * @details This is an unsigned char, which means the grid can be at most 255x255.
         * This is more than enough for our purposes.
         * @date 2023-12-06
         * @return The number of columns in the grid.
         */
        unsigned char GetCols() const;
        /**
         * @brief Set the number of columns in the grid.
         * @details This is an unsigned char, which means the grid can be at most 255x255.
         * This is more than enough for our purposes.
         * @date 2023-12-06
         * @param cols The number of columns in the grid.
         */
        void SetCols(unsigned char cols);

        /**
         * @brief Get the grid itself.
         * @details This is a 2D array of Cell pointers.
         * @date 2023-12-06
         * @return The grid itself.
         * @see Cell
         */
        const std::vector<std::vector<Cell *>> &GetGrid() const;
        /**
         * @brief Set the grid itself.
         * @details This is a 2D array of Cell pointers.
         * @date 2023-12-06
         * @param newGrid The new grid.
         * @see Cell
         */
        void SetGrid(const std::vector<std::vector<Cell *>> &newGrid);

        /**
         * @brief Get the default Piece for the grid.
         * @details This is the Piece that will be used to reset the grid.
         * @date 2023-12-06
         * @return The default Piece for the grid.
         * @see Piece
         */
        Piece *GetDefaultPiece() const;
        /**
         * @brief Set the default Piece for the grid.
         * @details This is the Piece that will be used to reset the grid.
         * @date 2023-12-06
         * @param defaultPiece The new default Piece for the grid.
         * @see Piece
         */
        void SetDefaultPiece(Piece *defaultPiece);

        /**
         * @brief Get the last changed element.
         * @details This is a pair of unsigned chars that stores the row and column of the last changed element.
         * @date 2023-12-06
         * @return The last changed element.
         */
        Piece *GetPieceAt(unsigned char row, unsigned char col) const;
        /**
         * @brief Set the last changed element.
         * @details This is a pair of unsigned chars that stores the row and column of the last changed element.
         * @date 2023-12-06
         * @param lastChangedChar The new last changed element.
         * @see Piece
         * @see Cell
         * @see Grid
         */
        void SetPieceAt(unsigned char row, unsigned char col, Piece *piece, bool force_null = false);

        /**
         * @brief Get the last changed element.
         * @details This is a pair of unsigned chars that stores the row and column of the last changed element.
         * @date 2023-12-06
         * @return The last changed element.
         */
        Cell *GetCellAt(unsigned char row, unsigned char col) const;
        /**
         * @brief Set the last changed element.
         * @details This is a pair of unsigned chars that stores the row and column of the last changed element.
         * @date 2023-12-06
         * @param force_null Allows to pass a nullptr to the cell.
         * @see Piece
         * @see Cell
         * @see Grid
         */
        void SetCellAt(unsigned char row, unsigned char col, Cell *cell, bool force_null = false);
        /**
         * @brief Set the last changed element.
         * @details This is a pair of unsigned chars that stores the row and column of the last changed element.
         * @date 2023-12-06
         * @param force_null Allows to pass a nullptr to the cell.
         * @see Piece
         * @see Cell
         */
        void SetCellAt(unsigned char row, unsigned char col, Piece *piece, bool force_null = false);

        /**
         * @brief Get the last changed element.
         * @details This is a pair of unsigned chars that stores the row and column of the last changed element.
         * @date 2023-12-06
         * @return The last changed element.
         */
        std::pair<unsigned char, unsigned char> GetLastChangedChar() const;

        // Overload the [] operator to access the grid.
    public:
        /**
         * @brief Overload the [] operator to access the grid.
         * @details This is a 2D array of Cell pointers.
         * @date 2023-12-06
         * @return The grid itself.
         * @see Cell
         */
        std::vector<Cell *> &operator[](size_t index);

        /**
         * @brief Overload the [] operator to access the grid.
         * @details This is a 2D array of Cell pointers.
         * @date 2023-12-06
         * @return The grid itself.
         * @see Cell
         */
        const std::vector<Cell *> &operator[](size_t index) const;

        // Public methods
    public:
        /**
         * @brief Get the grid as a string.
         * @details This will return a string representation of the grid.
         * @date 2023-12-06
         * @return The grid as a string.
         */
        const std::string GetGridSize() const;
        /**
         * @brief Get the grid as a string.
         * @details This will return a string representation of the grid.
         * @date 2023-12-06
         * @return The grid as a string.
         */
        void ResetGrid();
        /**
         * @brief Get the grid as a string.
         * @details This will return a string representation of the grid.
         * @date 2023-12-06
         * @return The grid as a string.
         */
        void ResetGridWithNewSize(unsigned char newRows, unsigned char newCols, Piece *defaultPiece = nullptr);
        /**
         * @brief Get the grid as a string.
         * @details This will return a string representation of the grid.
         * @date 2023-12-06
         * @return The grid as a string.
         */
        void ResetGridWithNewDefaultPiece(Piece *defaultPiece = nullptr);

        /**
         * @brief Get the grid as a string.
         * @details This will return a string representation of the grid.
         * @date 2023-12-06
         * @return The grid as a string.
         */
        std::string GetGridAsString();

        // bool CheckForRecurringStringInRow(const std::string &playerString, unsigned int dupCount);
        // bool CheckForRecurringStringInCol(const std::string &playerString, unsigned int dupCount);
        // bool CheckForRecurringStringInDiagonal(const std::string &playerString, unsigned int dupCount);
        // bool CheckForRecurringStringInAntiDiagonal(const std::string &playerString, unsigned int dupCount);

        // // This one is broken and should probably be removed...
        // std::string GetCharCenterMostElement() const;
        // std::pair<unsigned char, unsigned char> GetCenterMostCoords() const;
    };
}
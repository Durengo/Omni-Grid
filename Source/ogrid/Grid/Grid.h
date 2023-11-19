#pragma once

#include <string>
#include <vector>

#include "fmt/format.h"

#include "GameDefinition/Piece.h"

namespace OGRID
{
    class PieceOnGrid
    {
        Piece *m_Piece;
        unsigned char m_Row;
        unsigned char m_Col;
        int m_SideOwner;
    };

    class Grid
    {
    private:
        // Limit grid size to 255x255.
        unsigned char rows;
        unsigned char cols;
        // Use a 2D array of strings to represent the grid.
        std::vector<std::vector<std::string>> grid;

        // Store default string for resetting the grid.
        std::string defaultString;

        // Store which element was last changed.
        unsigned char lastChangedChar[2] = {0, 0};

    public:
        // Constructors & Destructors
        Grid(unsigned char rows, unsigned char cols, const std::string &initialString = ".");
        ~Grid();

        // Getters & Setters
    public:
        unsigned char GetRows() const;
        void SetRows(unsigned char rows);

        unsigned char GetCols() const;
        void SetCols(unsigned char cols);

        const std::vector<std::vector<std::string>> &GetGrid() const;
        void SetGrid(const std::vector<std::vector<std::string>> &newGrid);

        std::string GetDefaultString() const;
        void SetDefaultString(const std::string &defaultString);

        std::string GetStringAt(unsigned char row, unsigned char col) const;
        void SetStringAt(unsigned char row, unsigned char col, const std::string &newString);

        std::pair<unsigned char, unsigned char> GetLastChangedChar() const;

        // Overload the [] operator to access the grid.
    public:
        std::vector<std::string> &operator[](size_t index);

        const std::vector<std::string> &operator[](size_t index) const;

        // Public methods
    public:
        const std::string GetGridSize() const;
        void ResetGrid();
        void ResetGridWithNewSize(unsigned char newRows, unsigned char newCols, const std::string &newString = ".");
        void ResetGridWithNewString(const std::string &newString);

        bool CheckForRecurringStringInRow(const std::string &playerString, unsigned int dupCount);
        bool CheckForRecurringStringInCol(const std::string &playerString, unsigned int dupCount);
        bool CheckForRecurringStringInDiagonal(const std::string &playerString, unsigned int dupCount);
        bool CheckForRecurringStringInAntiDiagonal(const std::string &playerString, unsigned int dupCount);

        // This one is broken and should probably be removed...
        std::string GetCharCenterMostElement() const;
        std::pair<unsigned char, unsigned char> GetCenterMostCoords() const;
    };
}

// Formatting for fmt library.
template <>
struct fmt::formatter<OGRID::Grid> : fmt::formatter<std::string>
{
    // Parses format specifications of the form '[:...]' which you can ignore.
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

    // Formats the Grid using provided format specifiers.
    template <typename FormatContext>
    auto format(const OGRID::Grid &grid, FormatContext &ctx)
    {
        // Use a memory buffer to store the temporary output.
        fmt::memory_buffer buf;

        fmt::format_to(std::back_inserter(buf), "\n");

        for (int i = 0; i < grid.GetRows(); i++)
        {
            for (int j = 0; j < grid.GetCols(); j++)
            {
                // Assuming you want a space between characters in a row.
                if (j > 0)
                    fmt::format_to(std::back_inserter(buf), " ");
                // Format each character from the grid.
                fmt::format_to(std::back_inserter(buf), "{}", grid.GetGrid()[i][j]);
            }
            // Add a newline after each row, except the last one.
            if (i < grid.GetRows() - 1)
                fmt::format_to(std::back_inserter(buf), "\n");
        }

        // Output the buffer to the formatting context and return the iterator.
        return fmt::format_to(ctx.out(), "{}", to_string(buf));
    }
};
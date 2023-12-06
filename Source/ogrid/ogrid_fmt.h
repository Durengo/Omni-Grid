#pragma once

#include <string>

#include "fmt/format.h"

#include "Grid/Grid.h"
#include "Player/Player.h"
#include "Player/Piece.h"
/**
 * @file ogrid_fmt.h
 * @brief This is used for fmt formatting from the OGRID namespace.
 * @details This is put in one file to avoid circular dependencies.
 * @date 2023-12-06
*/
// Formatting for fmt library.

// Grid formatting
/**
 * @brief This is used to format a Grid object into a string using fmt.
 * @details This should be used like this: fmt::format("{}", grid);
 * @date 2023-12-06
*/
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
                OGRID::Cell *cell = grid.GetGrid()[i][j];

                // Assuming you want a space between characters in a row.
                if (j > 0)
                    fmt::format_to(std::back_inserter(buf), " ");
                // Check if the cell pointer is not null and then access m_Piece
                if (cell != nullptr && cell->m_Piece != nullptr)
                    fmt::format_to(std::back_inserter(buf), "{}", cell->m_Piece->GetRepresentation());
                else
                    fmt::format_to(std::back_inserter(buf), " ");
                // fmt::format_to(std::back_inserter(buf), "{}", grid.GetGrid()[i][j]);
            }
            // Add a newline after each row, except the last one.
            if (i < grid.GetRows() - 1)
                fmt::format_to(std::back_inserter(buf), "\n");
        }

        // Output the buffer to the formatting context and return the iterator.
        return fmt::format_to(ctx.out(), "{}", to_string(buf));
    }
};

// Player formatting
/**
 * @brief This is used to format a PlayerType enum into a string using fmt.
 * @details This should be used like this: fmt::format("{}", playerType);
 * @date 2023-12-06
*/
template <>
struct fmt::formatter<OGRID::PlayerType> : formatter<std::string>
{
    template <typename FormatContext>
    auto format(OGRID::PlayerType p, FormatContext &ctx)
    {
        std::string name = p == OGRID::PlayerType::Human ? "Human" : "AI";
        return formatter<std::string>::format(name, ctx);
    }
};

/**
 * @brief This is used to format a Player object into a string using fmt.
 * @details This should be used like this: fmt::format("{}", player);
 * @date 2023-12-06
*/
template <>
struct fmt::formatter<OGRID::Player> : fmt::formatter<std::string>
{
    // Parses format specifications of the form '[:...]' which you can ignore.
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

    // Formats the Player using provided format specifiers.
    template <typename FormatContext>
    auto format(const OGRID::Player &player, FormatContext &ctx)
    {
        // Use a memory buffer to store the temporary output.
        fmt::memory_buffer buf;

        fmt::format_to(std::back_inserter(buf), "{} | {}", player.GetPlayerName(), player.GetPlayerType());

        // Output the buffer to the formatting context and return the iterator.
        return fmt::format_to(ctx.out(), "{}", to_string(buf));
    }
};
#include <durlib.h>

// #include "Core/GameInitializer.h"

#include <ogrid.h>

int main()
{
    DURLIB::Log::Init();

    CLI_INFO("Welcome to Omni Grid Sandbox!");

    // All the games are initialized in this class
    // Sandbox::GameInitializer::Start();

    // TESTING ABSTRACTIONS
    {
        OGRID::Grid *grid = new OGRID::Grid(3, 3);
        CLI_TRACE("Grid created: {}", grid->GetGridSize());

        CLI_TRACE("GRID:\n{}", grid->GetGridAsString());

        OGRID::XPiece *xPiece = new OGRID::XPiece();
        OGRID::OPiece *oPiece = new OGRID::OPiece();
        int startRow = 0, startCol = 0, endRow = 0, endCol = 0;

        if (xPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, xPiece);
        }
        else
        {
            CLI_TRACE("Invalid move");
        }

        CLI_TRACE("GRID:\n{}", grid->GetGridAsString());

        endRow++;
        endCol++;

        if (xPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, xPiece);
        }
        else
        {
            CLI_TRACE("Invalid move");
        }

        CLI_TRACE("GRID:\n{}", grid->GetGridAsString());

        endRow++;
        endCol++;

        if (xPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, xPiece);
        }
        else
        {
            CLI_TRACE("Invalid move");
        }

        CLI_TRACE("GRID:\n{}", grid->GetGridAsString());

        OGRID::GameStateChecker gameStateCheckerTicTacToe(new OGRID::TicTacToeStateCheck());
        CLI_INFO("Winner: {}", gameStateCheckerTicTacToe.CheckWin(grid));
        CLI_INFO("Is Draw?: {}", gameStateCheckerTicTacToe.IsDraw(grid));
    }
    {
        OGRID::Grid *grid = new OGRID::Grid(3, 3);
        CLI_TRACE("Grid created: {}", grid->GetGridSize());

        CLI_TRACE("GRID:\n{}", grid->GetGridAsString());

        OGRID::XPiece *xPiece = new OGRID::XPiece();
        OGRID::OPiece *oPiece = new OGRID::OPiece();
        int startRow = 0, startCol = 0, endRow = 0, endCol = 0;

        if (oPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, oPiece);
        }
        else
        {
            CLI_TRACE("Invalid move");
        }

        CLI_TRACE("GRID:\n{}", grid->GetGridAsString());

        endRow++;
        endCol++;

        if (oPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, oPiece);
        }
        else
        {
            CLI_TRACE("Invalid move");
        }

        CLI_TRACE("GRID:\n{}", grid->GetGridAsString());

        endRow++;
        endCol++;

        if (oPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, oPiece);
        }
        else
        {
            CLI_TRACE("Invalid move");
        }

        CLI_TRACE("GRID:\n{}", grid->GetGridAsString());

        OGRID::GameStateChecker gameStateCheckerTicTacToe(new OGRID::TicTacToeStateCheck());
        CLI_INFO("Winner: {}", gameStateCheckerTicTacToe.CheckWin(grid));
        CLI_INFO("Is Draw?: {}", gameStateCheckerTicTacToe.IsDraw(grid));
    }
    {
        // Force draw
        /*
        O X O
        O X X
        X O X
        */
        OGRID::Grid *grid = new OGRID::Grid(3, 3);
        CLI_TRACE("Grid created: {}", grid->GetGridSize());

        CLI_TRACE("GRID:\n{}", grid->GetGridAsString());

        OGRID::XPiece *xPiece = new OGRID::XPiece();
        OGRID::OPiece *oPiece = new OGRID::OPiece();
        int startRow = 0, startCol = 0, endRow = 0, endCol = 0;

        if (oPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, oPiece);
        }

        endCol++;

        if (xPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, xPiece);
        }

        endCol++;

        if (oPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, oPiece);
        }

        endRow++;
        endCol = 0;

        if (oPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, oPiece);
        }

        endCol++;

        if (xPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, xPiece);
        }

        endCol++;

        if (xPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, xPiece);
        }

        endRow++;
        endCol = 0;

        if (xPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, xPiece);
        }

        endCol++;

        if (oPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, oPiece);
        }

        endCol++;

        if (xPiece->isValidMove(grid, startRow, startCol, endRow, endCol))
        {
            CLI_TRACE("Valid move");
            grid->SetPieceAt(endRow, endCol, xPiece);
        }

        CLI_TRACE("GRID:\n{}", grid->GetGridAsString());

        OGRID::GameStateChecker gameStateCheckerTicTacToe(new OGRID::TicTacToeStateCheck());
        CLI_INFO("Winner: {}", gameStateCheckerTicTacToe.CheckWin(grid));
        CLI_INFO("Is Draw?: {}", gameStateCheckerTicTacToe.IsDraw(grid));
    }

#include <iostream>
    std::cin.get();

    return 0;
}
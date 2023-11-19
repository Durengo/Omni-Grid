#include "TicTacToePieces.h"

#include "Grid/Grid.h"

namespace OGRID
{
    bool XMoveRule::IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
    {
        return grid->GetPieceAt(toX, toY) == nullptr;
    }

    bool OMoveRule::IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
    {
        return grid->GetPieceAt(toX, toY) == nullptr;

        // Piece *startCellPiece = grid.GetPieceAt(startRow, startCol);
        // Piece *endCellPiece = grid.GetPieceAt(endRow, endCol);

        // if (startCellPiece == nullptr)
        // {
        //     return false;
        // }
        // // Start cell must be occupied by an O
        // if (startCellPiece->GetRepresentation() != "O")
        // {
        //     return false;
        // }
        // // Check if the end cell is unoccupied
        // if (endCellPiece != nullptr)
        // {
        //     return false;
        // }
        // return true;
    }

    XPiece::XPiece(Player *player)
        : Piece("X", player)
    {
        this->AddMoveRule(new XMoveRule());
    }

    OPiece::OPiece(Player *player)
        : Piece("O", player)
    {
        this->AddMoveRule(new OMoveRule());
    }
}
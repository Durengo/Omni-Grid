//
// Created by LastWeek on 20/11/2023.
//

#include <durlib/Log/Log.h>
#include "PieceRules.h"

#include "Grid/Grid.h"

namespace OGRID
{

    bool SimplePlaceMoveRule::IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
    {
        return grid->GetPieceAt(toY, toX) == nullptr;
    }

    bool NormalCheckersMoveRule::IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
    {
        if (toX == fromX || toY == fromY) {
            CLI_WARN("Invalid Attack Move.");
            return false;
        }

        // -1 = up, 1 = down
        int moveDirection = grid->GetPieceAt(fromY, fromX)->GetOwner()->GetSide() == 0 ? -1 : 1; // If white -> go up, if black -> go down
        if (moveDirection == 1 && toY < fromY) {
            CLI_WARN("Attempted to move backwards.");
            return false;
        }
        if (moveDirection == -1 && toY > fromY) {
            CLI_WARN("Attempted to move backwards.");
            return false;
        }
        if(toY == fromY + moveDirection && (toX == fromX + moveDirection || toX == fromX - moveDirection)){
            if (grid->GetPieceAt(toY, toX) == nullptr) {
                CLI_INFO("Valid Normal Checkers Move.");
                return true;
            }
        }
        CLI_WARN("Attempted to move onto an occupied cell.");
        return false;
    }

    bool JumpNormalCheckersAttackRule::IsValidAttack(Grid *grid, int fromX, int fromY, int toX, int toY, bool &canContinue) const
    {
        if (grid->GetPieceAt(toY, toX) != nullptr) { // Can't jump onto a cell that's occupied
            CLI_WARN("Attempted to jump onto an occupied cell.");
            return false;
        }

        if (toX == fromX || toY == fromY) {
            CLI_WARN("Invalid Attack Move.");
            return false;
        }

        canContinue = false;
        int enemyPieceY;
        int enemyPieceX;

        // 2 because we're jumping over a piece
        int side = grid->GetPieceAt(fromY, fromX)->GetOwner()->GetSide();
        int moveDirectionY = side == 0 ? -2 : 2;
        int enemyMoveDirectionY = moveDirectionY == 2 ? 1 : -1;

        if (moveDirectionY == 2 && toY < fromY) {
            CLI_WARN("Attempted to attack backwards.");
            return false;
        }
        if (moveDirectionY == -2 && toY > fromY) {
            CLI_WARN("Attempted to attack backwards.");
            return false;
        }

        if (toY == fromY + moveDirectionY && (toX == fromX + moveDirectionY || toX == fromX - moveDirectionY)) {
            enemyPieceY = fromY + enemyMoveDirectionY;
            if (toX == fromX + moveDirectionY) enemyPieceX = fromX + enemyMoveDirectionY;
            else if (toX == fromX - moveDirectionY) enemyPieceX = fromX - enemyMoveDirectionY;
        } else {
            CLI_WARN("Invalid Attack Move.");
            return false;
        }

        if (grid->GetPieceAt(enemyPieceY, enemyPieceX) == nullptr) {
            CLI_WARN("Attempted to jump over an empty cell.");
            return false;
        }

        bool isValid = false;
        if (grid->GetPieceAt(enemyPieceY, enemyPieceX)->GetOwner()->GetSide() != side){
            isValid = true;
            CLI_INFO("Valid Normal Checkers Attack.");
        } else {
            CLI_WARN("Attempted to jump over an allied piece.");
            isValid = false;
        }

        if (toY + moveDirectionY < grid->GetRows() && toY + moveDirectionY >= 0){ // If the jump is possible on Y axis
            if (toX + 2 < grid->GetCols()){ // And on the X axis to the right
                if (grid->GetPieceAt(toY + moveDirectionY, toX + 2) == nullptr) { // If jump space is empty
                    if (grid->GetPieceAt(toY + enemyMoveDirectionY, toX + 1) != nullptr) { // And there's something to jump over
                        if (grid->GetPieceAt(toY + enemyMoveDirectionY, toX + 1)->GetOwner()->GetSide() != side) { // And it's an enemy
                            canContinue = true;
                        }
                    }
                }
            }
            if (toX - 2 >= 0){ // Same but to the left
                if (grid->GetPieceAt(toY + moveDirectionY, toX - 2) == nullptr) {
                    if (grid->GetPieceAt(toY + enemyMoveDirectionY, toX - 1) != nullptr){
                        if (grid->GetPieceAt(toY + enemyMoveDirectionY, toX - 1)->GetOwner()->GetSide() != side) {
                            canContinue = true;
                        }
                    }
                }
            }
        }

        return isValid;
    }

    bool SuperCheckersMoveRule::IsValidMove(Grid *grid, int fromX, int fromY, int toX, int toY) const
    {
        if (grid->GetPieceAt(toY, toX) != nullptr) {
            CLI_WARN("Attempted to move onto an occupied cell.");
            return false;
        }

        if (toX == fromX || toY == fromY) {
            CLI_WARN("Invalid Attack Move.");
            return false;
        }

        // Go in between STARTINGPOS and ENDPOS to check if there are any pieces found
        int deltaX = toX > fromX ? 1 : -1;
        int deltaY = toY > fromY ? 1 : -1;
        for (int x = fromX + deltaX, y = fromY + deltaY; x != toX || y != toY; x += deltaX, y += deltaY) {
            if (grid->GetPieceAt(y, x) != nullptr) {
                CLI_WARN("Attempted to move over a piece.");
                return false;
            }
        }

        return true;
    }

    bool JumpSuperCheckersAttackRule::IsValidAttack(Grid *grid, int fromX, int fromY, int toX, int toY, bool &canContinue) const
    {
        canContinue = false;
        if (grid->GetPieceAt(toY, toX) != nullptr) {
            CLI_WARN("Attempted to jump onto an occupied cell.");
            return false;
        }

        if (toX == fromX || toY == fromY) {
            CLI_WARN("Invalid Attack Move.");
            return false;
        }

        int deltaX = toX > fromX ? 1 : -1;
        int deltaY = toY > fromY ? 1 : -1;

        // You can only jump one cell behind a piece
        // And if there isn't even a piece before ENDPOS, why bother calculating everything else.
        if (grid->GetPieceAt(toY-deltaY, toX-deltaX) == nullptr) {
            CLI_WARN("Attempted to jump over an empty cell. Must jump one cell forward over a piece.");
            return false;
        }

        // Try and find the first piece in the path
        int firstFoundPieceX = -1;
        int firstFoundPieceY = -1;
        for (int x = fromX + deltaX, y = fromY + deltaY; x != toX || y != toY; x += deltaX, y += deltaY) {
            if (grid->GetPieceAt(y, x) != nullptr) {
                if (firstFoundPieceX == -1) {
                    firstFoundPieceX = x;
                    firstFoundPieceY = y;
                } else {
                    CLI_WARN("No pieces to jump over found.");
                    return false;
                }
            }
        }

        // If the found piece is one cell behind the ENDPOS, then it's all good
        if (toX - deltaX != firstFoundPieceX && toY - deltaY != firstFoundPieceY) {
            CLI_WARN("No pieces to jump over found.");
            return false;
        }

        int side = grid->GetPieceAt(fromY, fromX)->GetOwner()->GetSide();
        bool isValid = false;
        if (grid->GetPieceAt(firstFoundPieceY, firstFoundPieceX)->GetOwner()->GetSide() != side){
            isValid = true;
            CLI_INFO("Valid Super Checkers Attack.");
        } else {
            CLI_WARN("Attempted to jump over an allied piece.");
        }

        while (!canContinue){
            // To check further available attacks, we check in all four directions from the piece.
            // First we check left and right going down
            for (deltaY = 1, deltaX = 1; toY + deltaY < grid->GetRows() && toX + deltaX < grid->GetCols() ; deltaY += 1, deltaX += 1){ // Go down and to the right
                if (grid->GetPieceAt(toY + deltaY, toX + deltaX) == nullptr) { // If jump space is empty
                    if (grid->GetPieceAt(toY + deltaY - 1, toX + deltaX - 1) != nullptr && // And there's something to jump over,
                    (toY + deltaY - 1 != fromY && toX + deltaX - 1 != fromX) && // not including yourself (pre-move)
                    (toY + deltaY - 1 != firstFoundPieceY && toX + deltaX - 1 != firstFoundPieceX)) { // Or the previously jumped over piece
                        if (grid->GetPieceAt(toY + deltaY - 1, toX + deltaX - 1)->GetOwner()->GetSide() != side) { // And it's an enemy
                            canContinue = true;
                            break;
                        }
                    }
                }
            }
            for (deltaY = 1, deltaX = -1; toY + deltaY < grid->GetRows() && toX + deltaX >= 0; deltaY += 1, deltaX -= 1){ // Go down and to the left
                if (grid->GetPieceAt(toY + deltaY, toX + deltaX) == nullptr) { // If jump space is empty
                    if (grid->GetPieceAt(toY + deltaY - 1, toX + deltaX + 1) != nullptr && // And there's something to jump over,
                    (toY + deltaY - 1 != fromY && toX + deltaX + 1 != fromX) && // not including yourself (pre-move)
                    (toY + deltaY - 1 != firstFoundPieceY && toX + deltaX + 1 != firstFoundPieceX)) { // Or the previously jumped over piece
                        if (grid->GetPieceAt(toY + deltaY - 1, toX + deltaX + 1)->GetOwner()->GetSide() != side) { // And it's an enemy
                            canContinue = true;
                            break;
                        }
                    }
                }
            }
            // Then left and right going up
            for (deltaY = -1, deltaX = -1; toY + deltaY >= 0 && toX + deltaX >= 0; deltaY -= 1, deltaX -= 1){ // Go up and to the left
                if (grid->GetPieceAt(toY + deltaY, toX + deltaX) == nullptr) { // If jump space is empty
                    if (grid->GetPieceAt(toY + deltaY + 1, toX + deltaX + 1) != nullptr && // And there's something to jump over,
                    (toY + deltaY + 1 != fromY && toX + deltaX + 1 != fromX) && // not including yourself (pre-move)
                    (toY + deltaY + 1 != firstFoundPieceY && toX + deltaX + 1 != firstFoundPieceX)) { // Or the previously jumped over piece
                        if (grid->GetPieceAt(toY + deltaY + 1, toX + deltaX + 1)->GetOwner()->GetSide() != side) { // And it's an enemy
                            canContinue = true;
                            break;
                        }
                    }
                }
            }
            for (deltaY = -1, deltaX = 1; toY + deltaY >= 0 && toX + deltaX < grid->GetCols(); deltaY -= 1, deltaX += 1){ // Go up and to the right
                if (grid->GetPieceAt(toY + deltaY, toX + deltaX) == nullptr) { // If jump space is empty
                    if (grid->GetPieceAt(toY + deltaY + 1, toX + deltaX - 1) != nullptr && // And there's something to jump over,
                    (toY + deltaY + 1 != fromY && toX + deltaX - 1 != fromX) && // not including yourself (pre-move)
                    (toY + deltaY + 1 != firstFoundPieceY && toX + deltaX - 1 != firstFoundPieceX)) { // Or the previously jumped over piece
                        if (grid->GetPieceAt(toY + deltaY + 1, toX + deltaX - 1)->GetOwner()->GetSide() != side) { // And it's an enemy
                            canContinue = true;
                            break;
                        }
                    }
                }
            }
            break;
        }

        return isValid;
    }
}
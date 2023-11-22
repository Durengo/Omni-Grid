#pragma once

// Core
#include "Player/Player.h"
#include "Player/Piece.h"
#include "Grid/Grid.h"

// Interface
#include "GameLogicInterface/IGameState.h"
#include "GameLogicInterface/IMoveRule.h"
#include "GameLogicInterface/IGame.h"

// Implementation
#include "GameLogicImplementation/GameStateExtensions.h"
#include "GameLogicImplementation/GameStateChecker.h"
#include "GameLogicImplementation/GameConfiguration.h"
#include "GameLogicImplementation/PieceRules.h"

// Games
// Tic Tac Toe
#include "Games/TicTacToe/TicTacToeStateCheck.h"
#include "Games/TicTacToe/TicTacToePieces.h"
#include "Games/TicTacToe/TicTacToe.h"
// Connect Four
#include "Games/ConnectFour/ConnectFourStateCheck.h"
#include "Games/ConnectFour/ConnectFourPieces.h"
#include "Games/ConnectFour/ConnectFour.h"
// Checkers
#include "Games/Checkers/CheckersStateCheck.h"
#include "Games/Checkers/CheckersPieces.h"
#include "Games/Checkers/Checkers.h"
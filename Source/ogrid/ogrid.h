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
#include "GameLogicImplementation/PieceMoveRules.h"

// Games
// #include "Games/ogrid_games.h"
#include "Games/TicTacToe/TicTacToeStateCheck.h"
#include "Games/TicTacToe/TicTacToePieces.h"
#include "Games/TicTacToe/TicTacToe.h"
#include "Games/ConnectFour/ConnectFourStateCheck.h"
#include "Games/ConnectFour/ConnectFourPieces.h"
#include "Games/ConnectFour/ConnectFour.h"
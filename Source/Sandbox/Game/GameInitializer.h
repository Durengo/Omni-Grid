//
// Created by LastWeek on 11/11/2023.
//

#pragma once

#include <Player/Player.h>
#include <GUI/TicTacToeGUI.h>
#include <GUI/TicTacToeGUIInstance.h>

namespace Sandbox {
    class GameInitializer {
    public:
        // Starts the app and gives choice of games
        static void Start();
    private:
        static void StartTicTacToe();
    };
}
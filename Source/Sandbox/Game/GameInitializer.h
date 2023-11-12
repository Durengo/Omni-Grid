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
        static void Start();
    private:
        static void StartTicTacToe();
    };
}
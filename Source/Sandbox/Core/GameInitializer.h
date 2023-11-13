#pragma once

namespace Sandbox {
    class GameInitializer {
    public:
        // Starts the app and gives choice of games
        static void Start();
    private:
        static void StartTicTacToe();
        static void StartConnectFour();
    };
}
#pragma once

#include <Helpers/Singleton.h>

#include "TicTacToeGUI.h"

namespace OGRIDSandbox
{
    class TicTacToeGUIInstance : OGRID::Singleton
    {
    private:
        static TicTacToeGUI *i_instance;

    public:
        static void DeleteInstance();

        // Getters & Setters
    public:
        static TicTacToeGUI *GetInstance();

    private:
        static bool CheckInit();
    };
}

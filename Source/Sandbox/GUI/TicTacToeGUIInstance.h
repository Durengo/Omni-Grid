//
// Created by LastWeek on 12/11/2023.
//

#pragma once

#include "../../Generics/Singleton.h"
#include "TicTacToeGUI.h"

namespace OGRIDSandbox{
    class TicTacToeGUIInstance : GENERICS::Singleton {
    private:
        static OGRIDSandbox::TicTacToeGUI *i_instance;

    public:
        static void DeleteInstance();

        // Getters & Setters
    public:
        static TicTacToeGUI *GetInstance();

    private:
        static bool CheckInit();
    };
}



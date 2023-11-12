//
// Created by LastWeek on 11/11/2023.
//
#pragma once

#include <durlib.h>
#include "TicTacToeLogic.h"
#include "../../Generics/Singleton.h"

namespace OGRIDSandbox{
    class TicTacToeInstance : GENERICS::Singleton {
    private:
        static TicTacToeLogic* i_instance;

    public:
        static void DeleteInstance();

        static TicTacToeLogic *GetInstance();
        static bool CheckInit();
    };
}



#pragma once

#include <Helpers/Singleton.h>
#include "TicTacToeLogic.h"

namespace OGRIDSandbox
{
    class TicTacToeInstance : OGRID::Singleton
    {
    private:
        static TicTacToeLogic *i_instance;

    public:
        static void DeleteInstance();

        static TicTacToeLogic *GetInstance();
        static bool CheckInit();
    };
}

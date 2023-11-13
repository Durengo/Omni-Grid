#pragma once

#include <Helpers/Singleton.h>
#include "ConnectFourLogic.h"


namespace OGRIDSandbox
{
    class ConnectFourInstance : OGRID::Singleton
    {
    private:
        static ConnectFourLogic *i_instance;

    public:
        static void DeleteInstance();

        static ConnectFourLogic *GetInstance();
        static bool CheckInit();
    };
}

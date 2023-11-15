#pragma once

#include <Helpers/Singleton.h>

#include "ConnectFourGUI.h"

namespace OGRIDSandbox
{
    class ConnectFourGUIInstance : OGRID::Singleton
    {
    private:
        static ConnectFourGUI *i_instance;

    public:
        static void DeleteInstance();

        // Getters & Setters
    public:
        static ConnectFourGUI *GetInstance();

    private:
        static bool CheckInit();
    };
}

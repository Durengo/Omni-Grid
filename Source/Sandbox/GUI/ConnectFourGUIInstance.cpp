#include "ConnectFourGUIInstance.h"

#include <durlib.h>

namespace OGRIDSandbox
{
    ConnectFourGUI *ConnectFourGUIInstance::i_instance{nullptr};

    void ConnectFourGUIInstance::DeleteInstance()
    {
        // std::lock_guard<std::mutex> lock(i_mutex);
        if (i_instance != nullptr)
        {
            delete i_instance;
            i_instance = nullptr;
        }
    }

    ConnectFourGUI *ConnectFourGUIInstance::GetInstance()
    {
        // std::lock_guard<std::mutex> lock(i_mutex);
        if (i_instance == nullptr)
        {
            i_instance = new ConnectFourGUI();
        }
        DEBUG_ASSERT(i_instance, "TicTacToeGUI instance not initialized.");

        return i_instance;
    }

    bool ConnectFourGUIInstance::CheckInit()
    {
        if (i_instance == nullptr)
        {
            CLI_ERROR("TicTacToeGUI instance not initialized.");
            return false;
        }
        return true;
    }

}
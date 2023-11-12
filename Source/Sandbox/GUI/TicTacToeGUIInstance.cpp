#include "TicTacToeGUIInstance.h"

#include <durlib.h>

namespace OGRIDSandbox
{
    TicTacToeGUI *TicTacToeGUIInstance::i_instance{nullptr};

    void TicTacToeGUIInstance::DeleteInstance()
    {
        // std::lock_guard<std::mutex> lock(i_mutex);
        if (i_instance != nullptr)
        {
            delete i_instance;
            i_instance = nullptr;
        }
    }

    TicTacToeGUI *TicTacToeGUIInstance::GetInstance()
    {
        // std::lock_guard<std::mutex> lock(i_mutex);
        if (i_instance == nullptr)
        {
            i_instance = new TicTacToeGUI();
        }
        DEBUG_ASSERT(i_instance, "TicTacToeGUI instance not initialized.");

        return i_instance;
    }

    bool TicTacToeGUIInstance::CheckInit()
    {
        if (i_instance == nullptr)
        {
            CLI_ERROR("TicTacToeGUI instance not initialized.");
            return false;
        }
        return true;
    }

}

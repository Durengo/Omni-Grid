#include "TicTacToeInstance.h"

#include <durlib.h>

namespace OGRIDSandbox
{

    TicTacToeLogic *TicTacToeInstance::i_instance{nullptr};

    TicTacToeLogic *TicTacToeInstance::GetInstance()
    {
        // std::lock_guard<std::mutex> lock(i_mutex);
        if (i_instance == nullptr)
        {
            i_instance = new TicTacToeLogic();
        }
        return i_instance;
    }

    void TicTacToeInstance::DeleteInstance()
    {
        // std::lock_guard<std::mutex> lock(i_mutex);
        if (i_instance != nullptr)
        {
            delete i_instance;
            i_instance = nullptr;
        }
    }

    bool TicTacToeInstance::CheckInit()
    {
        if (i_instance == nullptr)
        {
            CLI_ERROR("TicTacToeLogic instance not initialized.");
            return false;
        }
        return true;
    }
}
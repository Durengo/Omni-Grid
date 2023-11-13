#include "ConnectFourInstance.h"

#include <durlib.h>

namespace OGRIDSandbox{

    ConnectFourLogic *ConnectFourInstance::i_instance{nullptr};

    ConnectFourLogic *ConnectFourInstance::GetInstance()
    {
        // std::lock_guard<std::mutex> lock(i_mutex);
        if (i_instance == nullptr)
        {
            i_instance = new ConnectFourLogic();
        }
        return i_instance;
    }

    void ConnectFourInstance::DeleteInstance() {
        // std::lock_guard<std::mutex> lock(i_mutex);
        if (i_instance != nullptr)
        {
            delete i_instance;
            i_instance = nullptr;
        }
    }

    bool ConnectFourInstance::CheckInit() {
        if (i_instance == nullptr)
        {
            CLI_ERROR("TicTacToeLogic instance not initialized.");
            return false;
        }
        return true;
    }
}
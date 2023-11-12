#include <durlib.h>
#include <GUI/TicTacToeGUIInstance.h>
#include <Game/GameInitializer.h>
#include "GUI/TicTacToeGUI.h"

int main()
{
    DURLIB::Log::Init();

    CLI_INFO("Welcome to Omni Grid Sandbox!");

    Sandbox::GameInitializer::Start();

    return 0;
}
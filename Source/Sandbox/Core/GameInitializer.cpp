#include "GameInitializer.h"

#include <durlib.h>
#include <ogrid.h>

#include "GUI/GameWindow.h"

namespace Sandbox
{
    void GameInitializer::Start()
    {
        int choice = 0;
        while (choice == 0)
        {
            CLI_TRACE("\n1. TicTacToe\n2. Connect Four");
            choice = DURLIB::GIBI(1, 2);
        }
        switch (choice)
        {
        case 1:
            GameWindow<OGRID::TicTacToe>().Start();
            break;
        case 2:
            GameWindow<OGRID::ConnectFour>().Start();
            break;
        default:
            CLI_TRACE("Invalid choice");
            break;
        }
    }
}
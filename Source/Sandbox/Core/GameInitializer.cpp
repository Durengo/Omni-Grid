#include "GameInitializer.h"

#include <durlib.h>
#include <ogrid.h>

#include "GUI/GameWindow.h"

#include "User/User.h"

namespace Sandbox
{
    void GameInitializer::Start(OGRID::User* user)
    {
        int choice = 0;
        while (choice == 0)
        {
            CLI_TRACE("\n1. TicTacToe\n2. Connect Four\n3. Checkers");
            choice = DURLIB::GIBI(1, 3);
        }
        switch (choice)
        {
        case 1:
            GameWindow<OGRID::TicTacToe>().Start(user);
            break;
        case 2:
            GameWindow<OGRID::ConnectFour>().Start(user);
            break;
        case 3:
            GameWindow<OGRID::Checkers>().Start(user);
            break;
        default:
            CLI_TRACE("Invalid choice");
            break;
        }
    }
}
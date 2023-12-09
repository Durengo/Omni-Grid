#include <durlib.h>
#include <ogrid.h>

#include "Core/GameInitializer.h"
#include "UserMenu/UserMenu.h"

/**
 * @file main.cpp
 * @brief Main entry point
 * @date 2023-12-06
 */

int main()
{
    DURLIB::Log::Init();

    CLI_INFO("Welcome to Omni Grid Sandbox!");

    Sandbox::UserMenu userMenu;
    userMenu.Start();

    return 0;
}
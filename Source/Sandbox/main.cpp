#include <durlib.h>
#include <ogrid.h>

#include "Core/GameInitializer.h"

/**
 * @file main.cpp
 * @brief Main entry point
 * @date 2023-12-06
 */

int main()
{
    DURLIB::Log::Init();

    CLI_INFO("Welcome to Omni Grid Sandbox!");

    // All the games are initialized in this class
    Sandbox::GameInitializer::Start();

    return 0;
}
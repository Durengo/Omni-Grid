#include <durlib.h>
#include "GUI/GUI.h"

int main()
{
    DURLIB::Log::Init();

    CLI_INFO("Welcome to Omni Grid Sandbox!");

    OGRIDSandbox::GUI::Initialize();
    OGRIDSandbox::GUI *gui = OGRIDSandbox::GUI::GetInstance();

    OGRID::Player *p1 = new OGRID::Player("Player1", OGRID::PlayerType::Human);
    OGRID::Player *p2 = new OGRID::Player("Player2", OGRID::PlayerType::Human);

    unsigned char dimensions = 3;

    CLI_TRACE("Input the dimensions of the grid (3-10): ");
    dimensions = static_cast<unsigned char>(DURLIB::GIBI(3, 10));

    int choice = 0;
    while (choice == 0)
    {
        CLI_TRACE("\n1. Start as X\n2. Start as O\n3. Random");
        choice = DURLIB::GIBI(1, 3);
    }

    if (choice == 1)
    {
        p1->SetPlayerMoveType(OGRID::MoveType::X);
        p2->SetPlayerMoveType(OGRID::MoveType::O);
        gui->SetRandomizeFirstPlayer(false);
        gui->SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                      .setGameName("TicTacToe")
                                      .setGameDescription("TicTacToe Game")
                                      .setGrid(dimensions, dimensions, '.')
                                      .setMaxPlayers(2)
                                      .addPlayer(p1)
                                      .addPlayer(p2)
                                      .build());
    }
    else if (choice == 2)
    {
        p1->SetPlayerMoveType(OGRID::MoveType::O);
        p2->SetPlayerMoveType(OGRID::MoveType::X);
        gui->SetRandomizeFirstPlayer(false);
        gui->SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                      .setGameName("TicTacToe")
                                      .setGameDescription("TicTacToe Game")
                                      .setGrid(dimensions, dimensions, '.')
                                      .setMaxPlayers(2)
                                      .addPlayer(p2)
                                      .addPlayer(p1)
                                      .build());
    }
    else if (choice == 3)
    {
        gui->SetRandomizeFirstPlayer(true);
        gui->SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                      .setGameName("TicTacToe")
                                      .setGameDescription("TicTacToe Game")
                                      .setGrid(dimensions, dimensions, '.')
                                      .setMaxPlayers(2)
                                      .addPlayer(p1)
                                      .addPlayer(p2)
                                      .build());
    }

    gui->InitializeWindow("OGRID", 800, 600, 60);
    gui->BeginMainLoop();

    return 0;
}
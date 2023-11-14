#include "GameInitializer.h"

#include <ogrid.h>
#include <GUI/TicTacToeGUI.h>
#include <GUI/TicTacToeGUIInstance.h>
#include <GUI/ConnectFourGUIInstance.h>
#include <Game/ConnectFourTurnManager.h>

#include "Game/TicTacToeTurnManager.h"

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
            StartTicTacToe();
            break;
        case 2:
            StartConnectFour();
            break;
        }
    }

    void GameInitializer::StartTicTacToe()
    {
        auto *p1 = new OGRID::Player("Player1", OGRID::Human);
        auto *p2 = new OGRID::Player("Player2", OGRID::Human);

        OGRIDSandbox::TicTacToeGUI *gui = OGRIDSandbox::TicTacToeGUIInstance::GetInstance();

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
                                          .build(new OGRIDSandbox::TicTacToeTurnManager()));
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
                                          .build(new OGRIDSandbox::TicTacToeTurnManager()));
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
                                          .build(new OGRIDSandbox::TicTacToeTurnManager()));
        }

        gui->InitializeWindow("Sandbox", 800, 600, 60);
        gui->BeginMainLoop();
    }

    void GameInitializer::StartConnectFour()
    {
        auto *p1 = new OGRID::Player("Player1", OGRID::Human);
        auto *p2 = new OGRID::Player("Player2", OGRID::Human);

        OGRIDSandbox::ConnectFourGUI *gui = OGRIDSandbox::ConnectFourGUIInstance::GetInstance();

        unsigned char dimensions = 7;

        int choice = 0;
        while (choice == 0)
        {
            CLI_TRACE("\n1. Start as RED\n2. Start as BLACK\n3. Random");
            choice = DURLIB::GIBI(1, 3);
        }

        // I WILL CONTINUE TO USE X AND O https://i.imgur.com/of0oR9s.mp4
        if (choice == 1)
        {
            p1->SetPlayerMoveType(OGRID::MoveType::X);
            p2->SetPlayerMoveType(OGRID::MoveType::O);
            gui->SetRandomizeFirstPlayer(false);
            gui->SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                          .setGameName("ConnectFour")
                                          .setGameDescription("ConnectFour Game")
                                          .setGrid(dimensions, dimensions, '.')
                                          .setMaxPlayers(2)
                                          .addPlayer(p1)
                                          .addPlayer(p2)
                                          .build(new OGRIDSandbox::ConnectFourTurnManager()));
        }
        else if (choice == 2)
        {
            p1->SetPlayerMoveType(OGRID::MoveType::O);
            p2->SetPlayerMoveType(OGRID::MoveType::X);
            gui->SetRandomizeFirstPlayer(false);
            gui->SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                          .setGameName("ConnectFour")
                                          .setGameDescription("ConnectFour Game")
                                          .setGrid(dimensions, dimensions, '.')
                                          .setMaxPlayers(2)
                                          .addPlayer(p2)
                                          .addPlayer(p1)
                                          .build(new OGRIDSandbox::ConnectFourTurnManager()));
        }
        else if (choice == 3)
        {
            gui->SetRandomizeFirstPlayer(true);
            gui->SetGameConfiguration(OGRID::GameConfigurationBuilder()
                                          .setGameName("ConnectFour")
                                          .setGameDescription("ConnectFour Game")
                                          .setGrid(dimensions, dimensions, '.')
                                          .setMaxPlayers(2)
                                          .addPlayer(p1)
                                          .addPlayer(p2)
                                          .build(new OGRIDSandbox::ConnectFourTurnManager()));
        }

        gui->InitializeWindow("Sandbox", 800, 600, 60);
        gui->BeginMainLoop();
    }
}
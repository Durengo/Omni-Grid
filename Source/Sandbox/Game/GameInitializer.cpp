//
// Created by LastWeek on 11/11/2023.
//




#include "GameInitializer.h"

namespace Sandbox {

    void GameInitializer::Start() {
        int choice = 0;
        while (choice == 0)
        {
            CLI_TRACE("\n1. TicTacToe");
            choice = DURLIB::GIBI(1, 1);
        }
        switch (choice) {
            case 1:
                StartTicTacToe();
                break;
        }
    }

    void GameInitializer::StartTicTacToe() {
        auto *p1 = new GENERICS::Player("Player1", GENERICS::Human);
        auto *p2 = new GENERICS::Player("Player2", GENERICS::Human);

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
            p1->SetPlayerMoveType(GENERICS::MoveType::X);
            p2->SetPlayerMoveType(GENERICS::MoveType::O);
            gui->SetRandomizeFirstPlayer(false);
            gui->SetGameConfiguration(GENERICS::GameConfigurationBuilder()
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
            p1->SetPlayerMoveType(GENERICS::MoveType::O);
            p2->SetPlayerMoveType(GENERICS::MoveType::X);
            gui->SetRandomizeFirstPlayer(false);
            gui->SetGameConfiguration(GENERICS::GameConfigurationBuilder()
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
            gui->SetGameConfiguration(GENERICS::GameConfigurationBuilder()
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
}
#include "UserMenu.h"

#include <durlib.h>

#include <Tools/Database/DatabaseUserWrapper.h>

namespace Sandbox
{

    UserMenu::UserMenu()
        : m_Database(nullptr)
    {
    }

    UserMenu::~UserMenu()
    {
    }

    void UserMenu::Start()
    {
        m_Database = new SQLWRAP::Database("omni-grid.db");

        FirstRun();
    }

    void UserMenu::FirstRun()
    {
        std::string createUserTable = "CREATE TABLE IF NOT EXISTS User("
                                      "UserId INTEGER PRIMARY KEY,"
                                      "UserName TEXT NOT NULL,"
                                      "UserPassword TEXT NOT NULL,"
                                      "UserFirstName TEXT,"
                                      "UserLastName TEXT);";

        std::string createScoreTable = "CREATE TABLE IF NOT EXISTS Score("
                                       "ScoreId INTEGER PRIMARY KEY,"
                                       "UserId INTEGER,"
                                       "Wins INTEGER NOT NULL,"
                                       "Losses INTEGER NOT NULL,"
                                       "WinRate REAL NOT NULL,"
                                       "FOREIGN KEY(UserId) REFERENCES User(UserId));";

        m_Database->createTableFromString(createUserTable);
        m_Database->createTableFromString(createScoreTable);

        m_Database->displayAllTables();
    }

    void UserMenu::PreLoginMenu()
    {
        CLI_TRACE("Welcome to Omni Grid!");
        CLI_TRACE("0. Exit");
        CLI_TRACE("1. Login");
        CLI_TRACE("2. Register");

        int input = -1;

        while (input == -1)
        {
            CLI_TRACE("Please enter your choice: ");
            input = DURLIB::GIBI(0, 2);
        }

        switch (input)
        {
        case 0:
            exit(0);
            break;
        case 1:
            Login();
            break;
        case 2:
            // Register();
            break;
        default:
            CLI_FATAL("Invalid input");
            break;
        }
    }

    void UserMenu::Login()
    {
        CLI_TRACE("Login");

        std::string userName;
        std::string userPassword;

        CLI_TRACE("Please enter your username:");
        userName = DURLIB::GIBS();

        CLI_TRACE("Please enter your password:");
        userPassword = DURLIB::GIBS();

        if (SQLWRAP::Login(m_Database, userName, userPassword))
        {
            CLI_TRACE("Login successful!");
        }
        else
        {
            CLI_TRACE("Login failed!");
        }
    }

}
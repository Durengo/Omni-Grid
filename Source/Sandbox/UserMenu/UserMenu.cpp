#include "UserMenu.h"

#include <durlib.h>

#include <Tools/Database/DatabaseUserWrapper.h>
#include "Core/GameInitializer.h"

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
        bool looping = true;

        while (looping)
        {
            CLI_TRACE("0. Exit");
            CLI_TRACE("1. Login");
            CLI_TRACE("2. Register");
            CLI_TRACE("3. Show Database");

            int input = -1;

            while (input == -1)
            {
                CLI_TRACE("Please enter your choice: ");
                input = DURLIB::GIBI(0, 3);
            }

            switch (input)
            {
            case 0:
                looping = false;
                break;
            case 1:
                Login();
                m_User = nullptr;
                continue;
            case 2:
                Register();
                continue;
            case 3:
                m_Database->displayAllTables();
                continue;
            default:
                continue;
            }
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
            m_User = SQLWRAP::FetchUserData(m_Database, userName, userPassword);

            if (m_User == nullptr)
                throw std::runtime_error("Failed to fetch user data even though login was successful");

            m_User->Display();

            PostLoginMenu();
        }
        else
        {
            CLI_TRACE("Login failed!");
        }
    }

    void UserMenu::Register()
    {
        CLI_TRACE("Register");

        std::string userName;
        std::string userPassword;
        std::string userFirstName;
        std::string userLastName;

        CLI_TRACE("Please enter your username:");
        userName = DURLIB::GIBS();

        CLI_TRACE("Please enter your password:");
        userPassword = DURLIB::GIBS();

        CLI_TRACE("Please enter your first name:");
        userFirstName = DURLIB::GIBS();

        CLI_TRACE("Please enter your last name:");
        userLastName = DURLIB::GIBS();

        if (SQLWRAP::Register(m_Database, userName, userPassword, userFirstName, userLastName))
        {
            CLI_TRACE("Registration successful!");
        }
        else
        {
            CLI_TRACE("Registration failed!");
        }
    }

    void UserMenu::PostLoginMenu()
    {
        // SQLWRAP::UpdateUserScore(m_Database, m_User);

        bool looping = true;

        while (looping)
        {
            CLI_TRACE("0. Exit");
            CLI_TRACE("1. Play");
            CLI_TRACE("2. Show Score");

            int input = -1;

            while (input == -1)
            {
                CLI_TRACE("Please enter your choice: ");
                input = DURLIB::GIBI(0, 2);
            }

            switch (input)
            {
            case 0:
                looping = false;
                break;
            case 1:
                Sandbox::GameInitializer::Start(m_User);
                SQLWRAP::UpdateUserScore(m_Database, m_User);
                continue;
            case 2:
                m_User->DisplayScore();
            default:
                continue;
            }
        }
    }
}
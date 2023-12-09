#include "UserMenu.h"

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
        m_Database = new SQLWRAP::database("omni-grid.db");

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

}
#pragma once

#include <Tools/Database/database.h>
#include "User/User.h"
#include "User/Score.h"

/**
 * @file DatabaseUserWrapper.h
 * @brief Contains the DatabaseUserWrapper class
 * @date 2023-12-06
 */

namespace SQLWRAP
{
    // Attempt to login with the given username and password
    static bool Login(Database *db, const std::string &username, const std::string &password)
    {
        sqlite3_stmt *stmt;
        int rc;
        bool loginSuccess = false;
        std::string sql;

        // Open the database
        db->open();

        // SQL to get user with given username
        sql = "SELECT UserPassword FROM User WHERE UserName = ?;";

        rc = sqlite3_prepare_v2(db->getSQLDB(), sql.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK)
        {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db->getSQLDB()) << std::endl;
            return false;
        }

        // Bind the username to the prepared statement
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            // Compare the provided password with the stored password
            std::string storedPassword = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            if (password == storedPassword)
            {
                loginSuccess = true;
            }
        }

        sqlite3_finalize(stmt);

        // Close the database
        db->close();

        return loginSuccess;
    }

    static bool CheckUsernameDuplicates(Database *db, const std::string &username)
    {
        sqlite3_stmt *stmt;
        int rc;
        std::string sql;

        // Open the database
        db->open();

        // SQL to check if the username already exists
        sql = "SELECT UserName FROM User WHERE UserName = ?;";

        rc = sqlite3_prepare_v2(db->getSQLDB(), sql.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK)
        {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db->getSQLDB()) << std::endl;
            db->close();
            return false;
        }

        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        db->close();

        // Returns true if username exists
        return rc == SQLITE_ROW;
    }

    static bool Register(Database *db, const std::string &username, const std::string &password, const std::string &firstName, const std::string &lastName)
    {
        if (CheckUsernameDuplicates(db, username))
        {
            std::cerr << "Username already exists." << std::endl;
            return false;
        }

        sqlite3_stmt *stmt;
        int rc;
        std::string sql;

        // Open the database
        db->open();

        // SQL to insert a new user
        sql = "INSERT INTO User (UserName, UserPassword, UserFirstName, UserLastName) VALUES (?, ?, ?, ?);";

        rc = sqlite3_prepare_v2(db->getSQLDB(), sql.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK)
        {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db->getSQLDB()) << std::endl;
            db->close();
            return false;
        }

        // Bind the details to the prepared statement
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, firstName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, lastName.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE)
        {
            std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db->getSQLDB()) << std::endl;
            return false;
        }

        // Get the last inserted user ID
        int lastUserId = sqlite3_last_insert_rowid(db->getSQLDB());

        // SQL to insert a default score for the new user
        sql = "INSERT INTO Score (UserId, Wins, Losses, WinRate) VALUES (?, 0, 0, 0.0);";

        rc = sqlite3_prepare_v2(db->getSQLDB(), sql.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK)
        {
            std::cerr << "Failed to prepare statement for Score: " << sqlite3_errmsg(db->getSQLDB()) << std::endl;
            db->close();
            return false;
        }

        // Bind the user ID to the prepared statement
        sqlite3_bind_int(stmt, 1, lastUserId);

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        db->close();

        if (rc != SQLITE_DONE)
        {
            std::cerr << "Failed to execute statement for Score: " << sqlite3_errmsg(db->getSQLDB()) << std::endl;
            return false;
        }

        return true;
    }

    static OGRID::User *FetchUserData(Database *db, const std::string &username, const std::string &password)
    {
        sqlite3_stmt *stmt;
        int rc;
        std::string sql;

        // Open the database
        db->open();

        // SQL to fetch the user
        sql = "SELECT UserId, UserName, UserPassword, UserFirstName, UserLastName FROM User WHERE UserName = ? AND UserPassword = ?;";

        rc = sqlite3_prepare_v2(db->getSQLDB(), sql.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK)
        {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db->getSQLDB()) << std::endl;
            db->close();
            return nullptr;
        }

        // Bind the username and password to the prepared statement
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

        OGRID::User *user = nullptr;

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            unsigned int userId = sqlite3_column_int(stmt, 0);
            std::string userName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            std::string userPassword = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            std::string firstName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
            std::string lastName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));

            user = new OGRID::User(userId, userName, userPassword, firstName, lastName);

            // Now fetch the score for this user
            sql = "SELECT ScoreId, Wins, Losses, WinRate FROM Score WHERE UserId = ?;";
            sqlite3_prepare_v2(db->getSQLDB(), sql.c_str(), -1, &stmt, nullptr);
            sqlite3_bind_int(stmt, 1, userId);

            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                unsigned int scoreId = sqlite3_column_int(stmt, 0);
                unsigned int wins = sqlite3_column_int(stmt, 1);
                unsigned int losses = sqlite3_column_int(stmt, 2);
                float winRate = static_cast<float>(sqlite3_column_double(stmt, 3));

                // Assuming Score is a member of User and has a suitable constructor
                user->SetScore(new OGRID::Score(scoreId, userId, wins, losses, winRate));

                CLI_ERROR("SCORE: {0}, {1}, {2}, {3}, {4}", scoreId, userId, wins, losses, winRate);
            }
        }

        sqlite3_finalize(stmt);
        db->close();

        return user;
    }

    static sqlite3_stmt *prepareStatement(Database *db, const std::string &sql)
    {
        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db->getSQLDB(), sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db->getSQLDB()) << std::endl;
            return nullptr;
        }
        return stmt;
    }

    static bool bindParameters(sqlite3_stmt *stmt, OGRID::User *user)
    {
        if (!stmt || !user || !user->GetScore())
        {
            return false;
        }

        OGRID::Score *score = user->GetScore();
        sqlite3_bind_int(stmt, 1, score->GetWins());
        sqlite3_bind_int(stmt, 2, score->GetLosses());
        sqlite3_bind_double(stmt, 3, score->GetWinRate());
        sqlite3_bind_int(stmt, 4, user->GetUserId());

        return true;
    }

    static bool executeStatement(Database *db, sqlite3_stmt *stmt)
    {
        int rc, retryCount = 0;
        while (retryCount < 10)
        {
            rc = sqlite3_step(stmt);
            if (rc == SQLITE_DONE)
            {
                return true;
            }
            else if (rc == SQLITE_BUSY)
            {
                std::cerr << "SQLite database is locked, retrying..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                retryCount++;
            }
            else
            {
                std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db->getSQLDB()) << std::endl;
                return false;
            }
        }
        return false;
    }

    static void beginTransaction(Database *db)
    {
        char *errMsg = nullptr;
        sqlite3_exec(db->getSQLDB(), "BEGIN TRANSACTION;", nullptr, nullptr, &errMsg);
    }

    static void commitTransaction(Database *db)
    {
        char *errMsg = nullptr;
        sqlite3_exec(db->getSQLDB(), "COMMIT;", nullptr, nullptr, &errMsg);
    }

    static void rollbackTransaction(Database *db)
    {
        char *errMsg = nullptr;
        sqlite3_exec(db->getSQLDB(), "ROLLBACK;", nullptr, nullptr, &errMsg);
    }

    static bool TestUpdate(Database *db)
    {
        std::string sql = "UPDATE Score SET Wins = 1, Losses = 1, WinRate = 0.5 WHERE UserId = 1;";
        sqlite3_stmt *stmt = prepareStatement(db, sql);
        if (!stmt)
        {
            return false;
        }

        if (executeStatement(db, stmt))
        {
            std::cout << "Update successful" << std::endl;
            sqlite3_finalize(stmt);
            return true;
        }
        else
        {
            std::cerr << "Update failed" << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }
    }

    static bool UpdateUserScore(Database *db, OGRID::User *user)
    {
        if (user == nullptr || user->GetScore() == nullptr)
        {
            std::cerr << "User or User's Score is null." << std::endl;
            return false;
        }

        // Start a transaction
        beginTransaction(db);

        std::string sql = "UPDATE Score SET Wins = ?, Losses = ?, WinRate = ? WHERE UserId = ?;";
        sqlite3_stmt *stmt = prepareStatement(db, sql);
        if (!stmt || !bindParameters(stmt, user))
        {
            rollbackTransaction(db);
            return false;
        }

        bool result = executeStatement(db, stmt);
        sqlite3_finalize(stmt);

        if (result)
        {
            commitTransaction(db);
        }
        else
        {
            rollbackTransaction(db);
        }

        return result;
    }
}
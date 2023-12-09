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

        return rc == SQLITE_ROW; // Returns true if username exists
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
            sql = "SELECT Wins, Losses, WinRate FROM Score WHERE UserId = ?;";
            sqlite3_prepare_v2(db->getSQLDB(), sql.c_str(), -1, &stmt, nullptr);
            sqlite3_bind_int(stmt, 1, userId);

            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                unsigned int wins = sqlite3_column_int(stmt, 0);
                unsigned int losses = sqlite3_column_int(stmt, 1);
                float winRate = static_cast<float>(sqlite3_column_double(stmt, 2));

                // Assuming Score is a member of User and has a suitable constructor
                user->SetScore(new OGRID::Score(userId, wins, losses, winRate));
            }
        }

        sqlite3_finalize(stmt);
        db->close();

        return user;
    }
}
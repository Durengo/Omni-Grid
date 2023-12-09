#pragma once

#include <Tools/Database/database.h>

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
}

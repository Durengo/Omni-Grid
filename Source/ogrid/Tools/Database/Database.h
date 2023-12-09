#pragma once

#include "sqlite3.h"
#include <iostream>
#include <vector>

/**
 * @file database.h
 * @brief Contains the database class
 * @date 2023-12-09
 */

namespace SQLWRAP
{
  /**
   * @brief The Database class
   * @details This class is used to manage the database
   * @date 2023-12-09
   */
  class Database
  {
  private:
    /**
     * @brief The sqlite3 database
     * @date 2023-12-09
     */
    sqlite3 *SQLDB;

    /**
     * @brief The sqlite3 statement
     * @date 2023-12-09
     */
    sqlite3_stmt *stmt;

    /**
     * @brief The file path
     * @date 2023-12-09
     */
    const char *FILEPATH;

    /**
     * @brief The file path
     * @date 2023-12-09
     */
    std::string fpath;

    // Constructors & Destructors
  public:
    /**
     * @brief Construct a new Database object
     * @date 2023-12-09
     * @param path The path to the database
     */
    Database(const std::string &path);

    /**
     * @brief Destroy the Database object
     * @date 2023-12-09
     */
    ~Database();

    // Getters & Setters
  public:
    /**
     * @brief Get the SQLDB object
     * @date 2023-12-09
     * @return sqlite3* The sqlite3 database
     */
    sqlite3 *getSQLDB() const;

    /**
     * @brief Get the FILEPATH object
     * @date 2023-12-09
     * @return const char* The file path
     */
    std::string getFilePath() const;

    /**
     * @brief Set the FILEPATH object
     * @date 2023-12-09
     * @param path The file path
     */
    int getRows(const std::string &tableName);

    /**
     * @brief Set the FILEPATH object
     * @date 2023-12-09
     * @param path The file path
     */
    int getColumns(const std::string &tableName);

    // Methods
  public:
    /**
     * @brief Open a connection to the database
     * @date 2023-12-09
     */
    // Open a connection to the database
    void open();

    /**
     * @brief Close the connection to the database
     * @date 2023-12-09
     */
    // Close the connection to the database
    void close();

    /**
     * @brief Execute a statement
     * @date 2023-12-09
     * @param sql The statement to execute
     */
    // Clear the database by removing the .db file
    void clear();

    /**
     * @brief Execute a statement
     * @date 2023-12-09
     * @param sql The statement to execute
     */
    // Core callback function for sqlite3_exec
    static int callback(void *context, int columnCount, char **columnValues, char **columnName);

    /**
     * @brief Execute a statement
     * @date 2023-12-09
     * @param sql The statement to execute
     */
    // Create a table from a string, if a table with the same name already exists, the statement will not be executed
    void createTableFromString(const std::string &sqlCreateTable);

    /**
     * @brief Execute a statement
     * @date 2023-12-09
     * @param sql The statement to execute
     */
    // Display all tables in the database
    void displayAllTables();
  };
}
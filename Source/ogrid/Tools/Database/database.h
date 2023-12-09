#pragma once

#include "sqlite3.h"
#include <iostream>
#include <vector>

/**
 * @file database.h
 * @brief Contains the database class
 * @date 2023-12-06
 */

namespace SQLWRAP
{
  class database
  {
  private:
    sqlite3 *SQLDB;
    sqlite3_stmt *stmt;

    const char *FILEPATH;
    std::string fpath;

    // Constructors & Destructors
  public:
    database(const std::string &path);
    ~database();

    // Getters & Setters
  public:
    std::string getFilePath() const;

    int getRows(const std::string &tableName);
    int getColumns(const std::string &tableName);

    // Methods
  public:
    // Open a connection to the database
    void open();
    // Close the connection to the database
    void close();
    // Clear the database by removing the .db file
    void clear();
    // Core callback function for sqlite3_exec
    static int callback(void *context, int columnCount, char **columnValues, char **columnName);
    // Create a table from a string, if a table with the same name already exists, the statement will not be executed
    void createTableFromString(const std::string &sqlCreateTable);
    // Display all tables in the database
    void displayAllTables();
  };
}
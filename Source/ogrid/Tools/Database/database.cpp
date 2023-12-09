#include "database.h"

#include <durlib.h>

namespace SQLWRAP
{

  // Constructors & Destructors
  database::database(const std::string &path)
      : FILEPATH(path.c_str()), fpath(path)
  {
    sqlite3_open(FILEPATH, &SQLDB);
    if (SQLDB == nullptr)
    {
      CLI_ASSERT(SQLDB, "COULD NOT ESTABLISH LINK WITH DATABASE");
      delete (this);
    }
    else
    {
      CLI_INFO("DATABASE LINK ESTABLISHED");
      return;
    }
    this->close();
  }

  database::~database()
  {
  }

  // Getters & Setters

  std::string database::getFilePath() const
  {
    return fpath;
  }

  int database::getRows(const std::string &tableName)
  {
    sqlite3_stmt *stmt;
    int rc;
    int rowCount = 0;
    std::string sql;

    // Open the database
    this->open();

    // SQL to get row count
    sql = "SELECT COUNT(*) FROM " + tableName + ";";

    rc = sqlite3_prepare_v2(SQLDB, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
      throw std::runtime_error("Error preparing SQL statement: " + std::string(sqlite3_errmsg(SQLDB)));
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      rowCount = sqlite3_column_int(stmt, 0);
    }
    else
    {
      throw std::runtime_error("Table not found: " + tableName);
    }

    sqlite3_finalize(stmt);

    // Close the database
    this->close();

    return rowCount;
  }

  int database::getColumns(const std::string &tableName)
  {
    sqlite3_stmt *stmt;
    int rc;
    int columnCount = 0;
    std::string sql;

    // Open the database
    this->open();

    // SQL to get the first row of the table
    sql = "SELECT * FROM " + tableName + " LIMIT 1;";

    rc = sqlite3_prepare_v2(SQLDB, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
      throw std::runtime_error("Error preparing SQL statement: " + std::string(sqlite3_errmsg(SQLDB)));
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      columnCount = sqlite3_column_count(stmt);
    }
    else
    {
      throw std::runtime_error("Table not found: " + tableName);
    }

    sqlite3_finalize(stmt);

    // Close the database
    this->close();

    return columnCount;
  }

  // Methods

  void database::open()
  {
    if (sqlite3_open(fpath.c_str(), &SQLDB))
    {
      CLI_ERROR("FAILED TO OPEN DATABASE");
    }
    else
    {
      return;
    };
  }

  void database::close()
  {
    sqlite3_close(SQLDB);
  }

  void database::clear()
  {
    remove(fpath.c_str());
  }

  int database::callback(void *NotUsed, int argc, char **argv, char **azColName)
  {

    for (int i = 0; i < argc; i++)
    {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    /*for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << " ";
    }*/

    std::cout << std::endl;

    return 0;
  }

  void database::createTableFromString(const std::string &sqlCreateTable)
  {
    char *zErrMsg = nullptr;
    int rc;

    // Open the database
    this->open();

    // Execute SQL statement
    rc = sqlite3_exec(SQLDB, sqlCreateTable.c_str(), nullptr, nullptr, &zErrMsg);

    if (rc != SQLITE_OK)
    {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }
    else
    {
      fprintf(stdout, "Table created successfully\n");
    }

    // Close the database
    this->close();
  }

  void database::displayAllTables()
  {
    sqlite3_stmt *stmt;
    int rc;
    std::string sql;
    char *zErrMsg = nullptr;

    // Open the database
    this->open();

    // Fetch all table names
    sql = "SELECT name FROM sqlite_master WHERE type='table';";

    rc = sqlite3_prepare_v2(SQLDB, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
      fprintf(stderr, "Failed to fetch table names: %s\n", sqlite3_errmsg(SQLDB));
      return;
    }

    // Iterate over all table names
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
      std::string tableName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
      std::cout << "\nTable: " << tableName << std::endl;

      // Display all records from the table
      std::string selectSql = "SELECT * FROM " + tableName + ";";
      rc = sqlite3_exec(SQLDB, selectSql.c_str(), callback, nullptr, &zErrMsg);

      if (rc != SQLITE_OK)
      {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      }
    }

    sqlite3_finalize(stmt);

    // Close the database
    this->close();
  }
}
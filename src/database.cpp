#include "../include/database.h"
#include <iostream>
#include <sqlite3.h>

// Database connection
sqlite3 *db;

// Callback function for SQL queries
int callback(void *NotUsed, int argc, char **argv, char **colNames) {
    for (int i = 0; i < argc; i++) {
        std::cout << colNames[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    return 0;
}

// Initializes the database
void setupDatabase() {
    int rc = sqlite3_open("database/server.db", &db);
    if (rc) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS Requests (ID INTEGER PRIMARY KEY, IP TEXT, Request TEXT, Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);";
    char *errMsg;
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

// Inserts a log entry into the database
void logRequestToDB(const std::string &ip, const std::string &request) {
    std::string sql = "INSERT INTO Requests (IP, Request) VALUES ('" + ip + "', '" + request + "');";
    char *errMsg;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Database insert error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

// Closes the database
void closeDatabase() {
    sqlite3_close(db);
}

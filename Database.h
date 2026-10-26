#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <map>
#include "sqlite3.h"

// Simple wrapper for SQLite statements and queries
class Database {
private:
    sqlite3* db;

public:
    Database(const std::string& dbPath);
    ~Database();

    bool execute(const std::string& query);
    std::vector<std::map<std::string, std::string>> query(const std::string& query);
};

#endif // DATABASE_H

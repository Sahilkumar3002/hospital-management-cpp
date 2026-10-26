#include "Database.h"
#include <iostream>

Database::Database(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        db = nullptr;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

bool Database::execute(const std::string& query) {
    if (!db) return false;
    char* zErrMsg = 0;
    int rc = sqlite3_exec(db, query.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << "\n";
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

static int queryCallback(void* data, int argc, char** argv, char** azColName) {
    auto& results = *static_cast<std::vector<std::map<std::string, std::string>>*>(data);
    std::map<std::string, std::string> row;
    for (int i = 0; i < argc; i++) {
        row[azColName[i]] = argv[i] ? argv[i] : "NULL";
    }
    results.push_back(row);
    return 0;
}

std::vector<std::map<std::string, std::string>> Database::query(const std::string& queryStr) {
    std::vector<std::map<std::string, std::string>> results;
    if (!db) return results;
    
    char* zErrMsg = 0;
    int rc = sqlite3_exec(db, queryStr.c_str(), queryCallback, &results, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << "\n";
        sqlite3_free(zErrMsg);
    }
    return results;
}

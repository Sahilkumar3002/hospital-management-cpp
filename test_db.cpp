#include "Database.h"
#include <iostream>

int main() {
    Database db("hospital.db");
    auto results = db.query("SELECT * FROM Users;");
    std::cout << "Number of users: " << results.size() << "\n";
    for (const auto& row : results) {
        std::cout << "User: '" << row.at("username") << "' | Pass: '" << row.at("password") << "'\n";
    }
    return 0;
}

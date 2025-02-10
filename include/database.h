#ifndef DATABASE_H
#define DATABASE_H

#include <string>

void setupDatabase();
void logRequestToDB(const std::string &ip, const std::string &request);
void closeDatabase();

#endif

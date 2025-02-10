#ifndef LOGGER_H
#define LOGGER_H

#include <string>

void setupLogger();
std::string getCurrentTimestamp();
void logRequest(const std::string &clientIP, const std::string &requestType, const std::string &url);
void logError(const std::string &errorMessage);

#endif

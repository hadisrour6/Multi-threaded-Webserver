#include "../include/logger.h"
#include <iostream>
#include <fstream>
#include <ctime>

// Initializes log file
void setupLogger() {
    std::ofstream logFile("logs/server.log", std::ios::app);
    if (logFile.is_open()) {
        logFile << "Server started at: " << getCurrentTimestamp() << std::endl;
        logFile.close();
    }
}

// Returns current timestamp as string
std::string getCurrentTimestamp() {
    time_t now = time(0);
    char buf[80];
    struct tm *timeinfo = localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buf);
}

// Logs requests
void logRequest(const std::string &clientIP, const std::string &requestType, const std::string &url) {
    std::ofstream logFile("logs/server.log", std::ios::app);
    if (logFile.is_open()) {
        logFile << "[" << getCurrentTimestamp() << "] " << clientIP << " - " << requestType << " " << url << std::endl;
        logFile.close();
    }
}

// Logs errors
void logError(const std::string &errorMessage) {
    std::ofstream logFile("logs/server.log", std::ios::app);
    if (logFile.is_open()) {
        logFile << "[ERROR] " << getCurrentTimestamp() << " - " << errorMessage << std::endl;
        logFile.close();
    }
}

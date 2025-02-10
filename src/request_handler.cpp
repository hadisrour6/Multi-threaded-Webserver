#include "request_handler.h"
#include "logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>

std::string readFile(const std::string &filename) {
    std::ifstream file("static/" + filename);
    if (!file) return "404 Not Found";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void handleClient(int clientSocket) {
    char buffer[4096] = {0};
    read(clientSocket, buffer, 4096);
    std::string request(buffer);
    
    std::string filename = "index.html";
    if (request.find("GET /") != std::string::npos) {
        size_t start = request.find("GET /") + 5;
        size_t end = request.find(" ", start);
        std::string fileRequested = request.substr(start, end - start);
        if (!fileRequested.empty() && fileRequested != "/") {
            filename = fileRequested;
        }
    }

    std::string content = readFile(filename);
    std::stringstream response;
    if (content == "404 Not Found") {
        response << "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n" << content;
    } else {
        response << "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" << content;
    }

    send(clientSocket, response.str().c_str(), response.str().length(), 0);
    close(clientSocket);
}

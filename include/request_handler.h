#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>

void handleClient(int clientSocket);
std::string readFile(const std::string &filename);

#endif

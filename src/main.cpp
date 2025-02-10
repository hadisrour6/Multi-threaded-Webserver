#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <netinet/in.h>
#include <unistd.h>
#include "../include/request_handler.h"
#include "../include/logger.h"
#include "../include/threadpool.h"
#include "../include/database.h"

#define PORT 8080
#define MAX_THREADS 5

std::mutex queue_mutex;
std::condition_variable condition;
std::queue<int> clientQueue;
std::vector<std::thread> threadPool;

void workerThread() {
    while (true) {
        int clientSocket;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [] { return !clientQueue.empty(); });
            clientSocket = clientQueue.front();
            clientQueue.pop();
        }
        handleClient(clientSocket);
    }
}

int main() {
    setupDatabase();
    setupLogger();

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        logError("Socket creation failed");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        logError("Binding failed");
        return 1;
    }

    if (listen(serverSocket, 10) < 0) {
        logError("Listening failed");
        return 1;
    }

    std::cout << "Server running on port " << PORT << "...\n";

    for (int i = 0; i < MAX_THREADS; i++) {
        threadPool.emplace_back(workerThread);
    }

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            logError("Client connection failed");
            continue;
        }

        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            clientQueue.push(clientSocket);
        }
        condition.notify_one();
    }

    close(serverSocket);
    return 0;
}

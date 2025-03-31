#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>

class Server {
public:
    Server(int port);
    void start();

private:
    SOCKET serverSocket;
    int port;
    std::mutex coutMutex;
    void handleClient();
};

#endif // SERVER_H
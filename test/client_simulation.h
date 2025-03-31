#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>

class Client {
public:
    Client();
    ~Client();
    void send_message(const char* message);
    //void start();

private:
    //SOCKET clientSocket;
    std::mutex coutMutex;
    SOCKET _clientSocket;

};

#endif // CLIENT_H
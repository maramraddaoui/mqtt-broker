#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>

class ClientSimulation {
public:
    ClientSimulation();
    ~ClientSimulation();
    void send_message(std::vector<uint8_t> message);
    //void start();

private:
    //SOCKET clientSocket;
    std::mutex coutMutex;
    SOCKET _clientSocket;

};

#endif // CLIENT_H
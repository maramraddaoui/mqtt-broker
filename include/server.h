#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "mqtt_parser.h"

class Server {
public:
    Server(int port);
    void start();
    void handleClient();

private:
    SOCKET serverSocket;
    int port;
    MQTTParser mqttParser;
    std::mutex coutMutex;
};

#endif // SERVER_H
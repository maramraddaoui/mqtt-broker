#include "client_simulation.h"
#include <server.h>

int main() {
    Server mqttServer(1883);
    mqttServer.start();
    Sleep(2);
    Client client;
    const char* message = "Hello, Server!";
    client.send_message(message);
    Sleep(5);
    return 0;
}
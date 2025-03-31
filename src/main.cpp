#include "server.h"

int main() {
    Server mqttServer(1883);
    mqttServer.start();
    return 0;
}

#include "client_simulation.h"
#include <server.h>

int main() {
    Server mqttServer(1883);
    mqttServer.start();
    Sleep(2);
    ClientSimulation clientSimulation;
    //const char* message = "Hello, Server!";
    std::vector<uint8_t> connectPacket = {
        // Fixed Header
        0x10, 0x23,             // Packet Type (CONNECT), Remaining Length = 40
        // Variable Header
        0x00, 0x04, 'M', 'Q', 'T', 'T',     // Protocol Name
        0x04,                   // Protocol Level (MQTT 3.1.1)
        0xC2,                   // Connect Flags: Username + Password + Clean Session
        0x00, 0x3C,             // Keep Alive = 60 seconds
        // Payload
        0x00, 0x07,'C','l','i','e','n','t','1',
        0x00, 0x05, 'u','s','e','r','1',
        0x00, 0x07, 'p','a','s','s','1','2','3'
    };
    for (size_t i = 0; i < connectPacket.size(); ++i) {
        std::cout << reinterpret_cast<const char&>(connectPacket[i]);
    }
    std::cout << std::endl;
    clientSimulation.send_message(connectPacket);
    Sleep(5);
    return 0;
}
#include "mqtt_parser.h"


MQTTMessageType MQTTParser::parseMessageType(const std::vector<uint8_t>& packet) {
    uint8_t messageType = (packet[0] >> 4) & 0x0F;
    return static_cast<MQTTMessageType>(messageType);
}

MQTTFixedHeader MQTTParser::parseFixedHeader(const char* packet) {
    MQTTFixedHeader header;
    // Extraction du bit DUP (bits 4, 5, 6, 7)
    header.messageType = (packet[0] >> 4) & 0x0F;
    // Extraction du bit DUP (bit 3)
    header.dup = (packet[0] & 0x08) >> 3;
    // Extraction des bits QoS (bits 2 et 1)
    header.QoS = (packet[0] & 0x06) >> 1;
    // Extraction du bit RETAIN (bit 0)
    header.retain = (packet[0] & 0x01);
    // Extraction du byte length (byte 2)
    header.length = packet[1];
    return header;
}

Client MQTTParser::parseConnectPacket(const char* packet) {
    if (strlen(packet) < 10) {
        throw std::runtime_error("Invalid CONNECT packet: too short.");
    }

    size_t index = 2;  // Skip fixed header

    // Read protocol name length
    uint16_t protocolLength = (packet[index] << 8) | packet[index + 1];
    index += 2;

    // Read protocol name
    std::string protocolName = std::string(packet[index], packet[index + protocolLength]);
    index += protocolLength;

    // Read protocol level (version)
    int protocolLevel = packet[index++];

    // Read connect flags
    uint8_t flags = packet[index++];
    bool cleanSession = (flags & 0x02) != 0;
    bool willFlag = (flags & 0x04) != 0;
    int willQoS = (flags & 0x18) >> 3;
    bool willRetain = (flags & 0x20) != 0;
    bool usernameFlag = (flags & 0x80) != 0;
    bool passwordFlag = (flags & 0x40) != 0;

    // Read keep alive time
    int keepAlive = (packet[index] << 8) | packet[index + 1];
    index += 2;

    // Read client ID length
    uint16_t clientIdLength = (packet[index] << 8) | packet[index + 1];
    index += 2;

    // Read client ID
    std::string clientID = std::string(packet[index], packet[index + clientIdLength]);
    index += clientIdLength;

    Client client(clientID, willQoS, willRetain, willFlag, cleanSession, protocolName, protocolLevel, keepAlive);
    // Read Will Topic & Will Message if Will Flag is set
    if (willFlag) {
        uint16_t willTopicLength = (packet[index] << 8) | packet[index + 1];
        index += 2;
        std::string willTopic = std::string(packet[index], packet[index + willTopicLength]);
        client.setWillTopic(willTopic);
        index += willTopicLength;

        uint16_t willMessageLength = (packet[index] << 8) | packet[index + 1];
        index += 2;
        std::string willMessage = std::string(packet[index], packet[index + willMessageLength]);
        client.setWillMessage(willMessage);
        index += willMessageLength;
    }

    // Read Username if Username Flag is set
    if (usernameFlag) {
        uint16_t usernameLength = (packet[index] << 8) | packet[index + 1];
        index += 2;
        std::string username = std::string(packet[index], packet[index + usernameLength]);
        client.setUserName(username);
        index += usernameLength;
    }

    // Read Password if Password Flag is set
    if (passwordFlag) {
        uint16_t passwordLength = (packet[index] << 8) | packet[index + 1];
        index += 2;
        std::string password = std::string(packet[index], packet[index + passwordLength]);
        client.setPassword(password);
        index += passwordLength;
    }
    return client;
}

void MQTTParser::parsePublishPacket(const std::vector<uint8_t>& packet) {
    size_t index = 2; // Après l'en-tête fixe
    // Lire le nom du topic
    uint16_t topicNameLength = (packet[index] << 8) | packet[index + 1];
    index += 2;
    std::string topicName(packet.begin() + index, packet.begin() + index + topicNameLength);
    index += topicNameLength;
    // Lire l'identifiant du paquet si QoS > 0
    uint16_t packetIdentifier = 0;
    /*if (QoS > 0) {
        packetIdentifier = (packet[index] << 8) | packet[index + 1];
        index += 2;
    }*/
    // Lire le message (charge utile)
    std::string payload(packet.begin() + index, packet.end());
}

void MQTTParser::parsePacket(const char* packet) {
    MQTTFixedHeader fixedHeader = parseFixedHeader(packet);
    switch (static_cast<MQTTMessageType>(fixedHeader.messageType)) {
    case MQTTMessageType::CONNECT:
        parseConnectPacket(packet);
        break;
    case MQTTMessageType::PUBLISH:
        break;
    case MQTTMessageType::SUBSCRIBE:
        break;
    default:
        throw std::runtime_error("Type de paquet inconnu");
        break;
    }

}
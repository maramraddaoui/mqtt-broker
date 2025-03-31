#include "mqtt_parser.h"


MQTTMessageType MQTTParser::parseMessageType(const std::vector<uint8_t>& packet) {
    uint8_t messageType = (packet[0] >> 4) & 0x0F;
    return static_cast<MQTTMessageType>(messageType);
}

MQTTFixedHeader MQTTParser::parseFixedHeader(const std::vector<uint8_t>& packet) {
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

void MQTTParser::parsePacket(const std::vector<uint8_t>& packet) {
    MQTTFixedHeader fixedHeader = parseFixedHeader(packet);
    switch (static_cast<MQTTMessageType>(fixedHeader.messageType)) {
    case MQTTMessageType::CONNECT:
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

void MQTTParser::parseConnectPacket(const std::vector<uint8_t>& packet) {
    // Assurez-vous que le paquet est suffisamment long
    size_t index = 2; // Après l'en-tête fixe
    // Lire le nom du protocole
    uint16_t protocolNameLength = (packet[index] << 8) | packet[index + 1];
    index += 2;
    std::string protocolName(packet.begin() + index, packet.begin() + index + protocolNameLength);
    index += protocolNameLength;
    // Lire le niveau du protocole
    uint8_t protocolLevel = packet[index++];
    // Lire les flags de connexion
    uint8_t connectFlags = packet[index++];
    // Lire l'intervalle de maintien
    uint16_t keepAlive = (packet[index] << 8) | packet[index + 1];
    index += 2;
    // Lire l'identifiant du client
    uint16_t clientIdLength = (packet[index] << 8) | packet[index + 1];
    index += 2;
    std::string clientId(packet.begin() + index, packet.begin() + index + clientIdLength);
    index += clientIdLength;
    // Traiter les champs optionnels (will, username, password) en fonction des flags
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

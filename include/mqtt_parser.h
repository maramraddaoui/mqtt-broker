#include <vector>
#include <string>
#include <stdexcept>

enum class MQTTMessageType {
	CONNECT = 1,		// Connection request
	CONNACK = 2,		// Connect acknowledgment
	PUBLISH = 3,		// Publish message
	PUBACK = 4,			// Publish acknowledgment (QoS 1)
	PUBREC = 5,			// Publish received(QoS 2 delivery part 1)
	PUBREL = 6,			// Publish release(QoS 2 delivery part 2)
	PUBCOMP = 7,		// Publish complete(QoS 2 delivery part 3)
	SUBSCRIBE = 8,		// Subscribe request
	SUBACK = 9,			// Subscribe acknowledgment
	UNSUBSCRIBE = 10,	// Unsubscribe request
	UNSUBACK = 11,		// Unsubscribe acknowledgment
	PINGREQ = 12,		// PING request
	PINGRESP = 13,		// PING response
	DISCONNECT = 14,	// Disconnect notification
	AUTH = 15			// Authentication exchange
};

struct MQTTFixedHeader {
	uint8_t messageType;
	bool dup;
	uint8_t QoS;
	bool retain;
	uint8_t length;
};

class MQTTParser {
	//MQTTParser();
	MQTTMessageType parseMessageType(const std::vector<uint8_t>& packet);
	MQTTFixedHeader MQTTParser::parseFixedHeader(const std::vector<uint8_t>& packet);
	void parsePacket(const std::vector<uint8_t>& packet);
	void parseConnectPacket(const std::vector<uint8_t>& packet);
	void parsePublishPacket(const std::vector<uint8_t>& packet);
};
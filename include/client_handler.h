#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <iostream>
#include <vector>
#include <string>

class Client {
public:
	Client(std::string clientId, int qos, bool retain, bool flag, bool cleanSession, std::string protocolName, int version, int keepAlive);
	void setQos(const int qos);
	void setVersion(const int version);
	void setKeepAlive(const int keepAlive);
	void setFlag(const bool flag);
	void setRetain(const bool retain);
	void setCleanSession(const bool cleanSession);
	void setUserName(const std::string userName);
	void setPassword(const std::string password);
	void setWillMessage(const std::string willMessage);
	void setWillTopic(const std::string willTopic);
	int getQos() const;

private:
	std::vector<std::string> _subscribed_topics = {};
	std::string clientId;
	int qos = 0;
	bool retain = false;
	bool flag = false;
	bool cleanSession;
	std::string protocolName;
	int version;
	int keepAlive;
	std::string userName = "";
	std::string password = "";
	std::string willMessage = "";
	std::string willTopic = "";
};

#endif //CLIENT_HANDLER_H
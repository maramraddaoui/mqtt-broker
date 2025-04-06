#include "client_handler.h"

Client::Client(std::string clientId, int qos, bool retain, bool flag, bool cleanSession, std::string protocolName, int version, int keepAlive) {
	this->clientId = clientId;
	this->qos = qos;
	this->retain = retain;
	this->flag = flag;
	this->cleanSession = cleanSession;
	this->keepAlive = keepAlive;
	this->version = version;
	this->protocolName = protocolName;
}

void Client::setQos(const int qos) {
	this->qos = qos;
}

void Client::setVersion(const int version) {
	this->version = version;
}

void Client::setKeepAlive(const int keepAlive) {
	this->keepAlive = keepAlive;
}

void Client::setFlag(const bool flag) {
	this->flag = flag;
}

void Client::setRetain(const bool retain){
	this->retain = retain;
}

void Client::setCleanSession(const bool cleanSession) {
	this->cleanSession = cleanSession;
}

void Client::setUserName(const std::string userName) {
	this->userName = userName;
}

void Client::setPassword(const std::string password) {
	this->password = password;
}

void Client::setWillMessage(const std::string willMessage) {
	this->willMessage = willMessage;
}

void Client::setWillTopic(const std::string willTopic) {
	this->willTopic = willTopic;
}

int Client::getQos() const {
	return this->qos;
}
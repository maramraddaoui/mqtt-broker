#ifndef TOPIC_MANAGER_H
#define TOPIC_MANAGER_H

#include <iostream>
#include <string>

class TopicManager{
public:
	int connect();
	int subscribe(std::string topic);
	int unsubscribe(std::string topic);
	int publish(std::string topic, std::string message);
};
#endif //TOPIC_MANAGER_H

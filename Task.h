#pragma once
#include <string>

class Task
{
	std::string name;
	int id;

	//std::string day, std::string month, std::string year;
	//int hour, minutes;

	bool isDone;
public:
	Task(const std::string& name, int id);

	const std::string &getName() const;
	const std::string &getPriority() const;
	int getId() const;
	bool getIsDone() const;
};
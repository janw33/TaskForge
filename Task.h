#pragma once
#include <string>

class Task
{
	std::string name;
	std::uint64_t ID;

	//std::string day, std::string month, std::string year;
	//int hour, minutes;

	bool isDone;
public:
	Task(const std::string& name, std::uint64_t ID);

	const std::string &getName() const;
	std::uint64_t getID() const;
	bool getIsDone() const;

	void changeStatus();
};
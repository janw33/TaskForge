#pragma once
#include <string>

class Task
{
	std::string name;
	std::string priority;
	int id;
	bool isDone;
public:
	Task(const std::string& name, const std::string& priority, int id);

	const std::string &getName() const;
	const std::string &getPriority() const;
	int getId() const;
	bool getIsDone() const;
};
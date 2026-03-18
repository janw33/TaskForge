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
};
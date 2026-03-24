#pragma once
#include <vector>
#include <map>
#include "Task.h"

class Project
{
	std::string name;
	int id;

	std::vector<Task>tasks;
	int taskNextId;
public:
	Project(const std::string& name, int id);

	const std::string& getName() const;
	int getId() const;
};
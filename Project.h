#pragma once
#include <vector>
#include "Task.h"

class Project
{
	std::string name;
	int id;

public:
	Project(const std::string& name, int id);

	const std::string& getName() const;
	int getId() const;

	void showTasks();
	void addTask();
	void deleteTask();
};
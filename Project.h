#pragma once
#include <vector>
#include "Task.h"

class Project
{
	std::string name;
	int id;
	std::vector<Task>tasks;

public:
	Project(const std::string& name, int id);

	const std::string& getName() const;
	int getId() const;

	void showTasks();
	void addTask(const std::string& name, int id);
	void deleteTask();
};
#pragma once
#include <vector>
#include <string>
#include <map>
#include "Task.h"
#include "Interface.h"

class TaskManager
{
	Interface& ui;
	std::vector<Task>tasks;
	std::map<int, size_t>taskIdToIndex;
	int taskNextId;

public:
	TaskManager(Interface& ui);

	void addTask(); // add validation!
	void deleteTask();
};
#pragma once
#include <vector>
#include <string>
#include "Task.h"
#include "Interface.h"

class TaskManager
{
	Interface& ui;
	std::vector<Task>tasks;
	int nextId;
public:
	TaskManager(Interface& ui);

	void addTask(); // add validation!
};
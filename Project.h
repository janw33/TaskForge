#pragma once
#include <vector>
#include "Task.h"

class Project
{
	std::string name;
	std::uint64_t ID;
	std::vector<Task>tasks;
	std::uint64_t taskNextID;

public:
	Project(const std::string& name, std::uint64_t ID);

	const std::string& getName() const;
	std::uint64_t getID() const;
	const std::vector<Task> &getTasks() const;

	void showTasks();
	void addTask(const std::string& name);
	void deleteTask(size_t index);

	Task* findTaskByID(std::uint64_t ID);
	std::ptrdiff_t findTaskIndexByID(std::uint64_t ID);
};
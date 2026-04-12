#pragma once
#include <vector>
#include "Task.h"
#include "ProjectMember.h"

class Project
{
	std::string name;
	std::uint64_t ID;
	std::vector<Task>tasks;
	std::uint64_t taskNextID;
	std::vector<ProjectMember>members;

	std::ptrdiff_t findTaskIndexByID(std::uint64_t ID);

public:
	Project(const std::string& name, std::uint64_t ID, std::uint64_t userID, Role role);

	const std::string& getName() const;
	std::uint64_t getID() const;
	const std::vector<Task> &getTasks() const;
	const std::vector<ProjectMember> &getProjectMembers() const;

	void showTasks();
	void addTask(const std::string& name);
	bool deleteTask(std::uint64_t ID);

	Task* findTaskByID(std::uint64_t ID);

	ProjectMember* findMemberByID(std::uint64_t ID);

	void addMember(std::uint64_t ID, Role role);
	size_t findMemberIndexByID(std::uint64_t ID);
	void deleteMember(std::uint64_t ID);
};
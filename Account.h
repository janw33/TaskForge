#pragma once
#include <string>
#include "Project.h"

class Account
{
	std::string username;
	std::string password;
	int id;
	std::vector<Project>projects;
	Project* currentProject;
	int projectNextId;
public:
	Account(const std::string& username, const std::string& password, int id);

	const std::string& getUsername() const;
	const std::string& getPassword() const;
	int getId() const;
	const std::vector<Project>& getProjects() const;

	void setUsername(const std::string &newUsername);
	void setPassword(const std::string &newPassword);
	void setCurrentProject(size_t index);

	int findProjectIndexById(int id) const;
	void addProject(const std::string &name);
	void deleteProject(size_t index);
};
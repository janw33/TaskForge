#pragma once
#include <string>
#include <vector>
#include "Project.h"

class Account
{
	std::string username;
	std::string password;
	int id;
	std::vector<Project>projects;
	int projectNextId;
public:
	Account(const std::string& username, const std::string& password, int id);

	const std::string& getUsername() const;
	const std::string& getPassword() const;
	int getId() const;

	void setUsername(const std::string &newUsername);
	void setPassword(const std::string &newPassword);

	void addProject(const std::string &name);
};
#pragma once
#include <string>
#include "Project.h"

class Account
{
	private:
	std::string username;
	std::string password;
	std::uint64_t ID;
	std::vector<Project>projects;
	std::uint64_t projectNextID;
	
	public:
	Account(const std::string& username, const std::string& password, std::uint64_t ID);

	const std::string& getUsername() const;
	const std::string& getPassword() const;
	std::uint64_t getID() const;
	const std::vector<Project>& getProjects() const;

	void setUsername(const std::string &newUsername);
	void setPassword(const std::string &newPassword);

	Project* findProjectByID(std::uint64_t ID);
	std::ptrdiff_t findProjectIndexByID(std::uint64_t ID);
	void addProject(const std::string &name);
	void deleteProject(size_t index);
};
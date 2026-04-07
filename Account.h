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
	std::vector<std::uint64_t>friendsIDs;

	std::ptrdiff_t findProjectIndexByID(std::uint64_t ID);
	std::ptrdiff_t findFriendIndexByID(std::uint64_t ID);

	public:
	Account(const std::string& username, const std::string& password, std::uint64_t ID);

	const std::string& getUsername() const;
	const std::string& getPassword() const;
	std::uint64_t getID() const;
	const std::vector<Project>& getProjects() const;
	const std::vector<std::uint64_t> &getFriendsIDs() const;

	void setUsername(const std::string &newUsername);
	void setPassword(const std::string &newPassword);

	Project* findProjectByID(std::uint64_t ID);
	void addProject(const std::string &name, std::uint64_t ownerID, const std::string& ownerUsername);
	bool deleteProject(std::uint64_t ID);

	void addFriend(std::uint64_t ID);
	bool deleteFriend(std::uint64_t ID);
	bool isHeMyFriend(std::uint64_t ID);
};
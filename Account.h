#pragma once
#include <string>
#include "Project.h"

class Account
{
	private:
	std::string username;
	std::string password;
	std::uint64_t ID;
	std::vector<std::uint64_t>projectsIDs;
	std::vector<std::uint64_t>friendsIDs;

	std::ptrdiff_t findProjectsIDsIndexByID(std::uint64_t ID);
	size_t findFriendIndexByID(std::uint64_t ID);

	public:
	Account(const std::string& username, const std::string& password, std::uint64_t ID);

	const std::string& getUsername() const;
	const std::string& getPassword() const;
	std::uint64_t getID() const;
	const std::vector<std::uint64_t>& getProjectsIDs() const;
	const std::vector<std::uint64_t> &getFriendsIDs() const;

	void setUsername(const std::string &newUsername);
	void setPassword(const std::string &newPassword);

	void addProjectID(std::uint64_t ID);
	bool deleteProjectID(std::uint64_t ID);

	void addFriend(std::uint64_t ID);
	void deleteFriend(std::uint64_t ID);
	bool isHeMyFriend(std::uint64_t ID);

	bool ProjectValidator(std::uint64_t ID);
};
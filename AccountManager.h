#pragma once
#include "Account.h"

class AccountManager
{
	std::vector<Account>accounts;
	Account* currentAccount;
	int nextId;
public:
	AccountManager();

	//log in
	bool isUsernameTaken(const std::string& username) const;
	void addAccount(const std::string &username, const std::string &password);

	bool login(const std::string& username, const std::string& password);

	//settings
	void changeUsername(const std::string &newUsername);
	void changePassword(const std::string &newPassword);
	void deleteAccount();

	// projects
	int findCurrentProjectIndexById(int id) const;
	void addProjectToCurrent(const std::string &name);
	void deleteCurrentProject(size_t index);
	const std::vector<Project>& getCurrentProjects() const;

	void logout();
};
#pragma once
#include "Account.h"

class AccountManager
{
	std::vector<Account>accounts;
	Account* currentAccount;
	int nextId;

	int findAccountIndexById(int id);
public:
	AccountManager();

	int findCurrentAccountIndex();
	
	bool isUsernameTaken(const std::string& username) const;

	void addAccount(const std::string &username, const std::string &password);
	bool login(const std::string& username, const std::string& password);

	void changeUsername(const std::string &newUsername);
	void changePassword(const std::string &newPassword);
	void deleteAccount();

	void logout();

	const int getCurrentAccountId() const;
};
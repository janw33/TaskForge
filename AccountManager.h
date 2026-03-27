#pragma once
#include <vector>
#include "Account.h"

class AccountManager
{
	std::vector<Account>accounts;
	int currentAccountId;
	int nextId;

	int findAccountIndexById(int id);

	bool isUsernameTaken(const std::string& usernmame);
	bool areCredentialsValid(const std::string& username, const std::string& password);

	bool wantContinue(std::string &confirmation);

	void changeUsername();
	void changePassword();
	void deleteAccount(int &accountChoice, int &choice);

public:
	AccountManager(Interface& ui);
		
	void signUp(bool &logged); // dodaj haslo jako hash!
	void logIn(bool &logged);
	void settings(int &accountChoice);
};
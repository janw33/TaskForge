#pragma once
#include <vector>
#include "Account.h"
#include "Interface.h"
#include "UserValidator.h"

class AccountManager
{
	Interface& ui;
	std::vector<Account>accounts;
	int nextId;

	bool isUsernameTaken(const std::string& usernmame);
	bool areCredentialsValid(const std::string& username, const std::string& password);
public:
	AccountManager(Interface& ui);
		
	void signUp(bool &logged); // dodaj haslo jako hash!
	void logIn(bool &logged);
};
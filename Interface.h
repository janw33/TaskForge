#pragma once
#include "AccountManager.h"

class Interface
{
	AccountManager &accountManager;

	void printMenu();
	void signUp(bool &logged);
	void login(bool &logged);


	void printAccountMenu();
	void printProjectList();
	void showProjects();
	void addProject();
	void deleteProject();

	void printAccountSettings();
	void changeUsername();
	void changePassword();
	void deleteAccount(int &accountChoice);
	void accountSettings(int &accountChoice);
public:
	Interface(AccountManager& am);
	void run();
};
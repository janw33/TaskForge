#pragma once
#include "AccountManager.h"

class Interface
{
	AccountManager am;
public:
//Menu
	void printMenu();
	void printAccountMenu();
	void printAccountSettings();
	void printProjectMenu();
//ui AccountManager 
	void signUp();
	void logIn();
	void accountSettings();
};
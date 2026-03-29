#pragma once
#include "Storage.h"
#include "Session.h"

class Interface
{
	Storage &storage;
	Session &session;

	void printMenu();
	void signUp(bool &logged);
	void login(bool &logged);


	void printAccountMenu();

	void printProjectList();

	void printProjectMenu();
	void showTasks();
	void addTask();
	void deleteTask();
	void insideProject();
	void showProjects();

	void addProject();
	void deleteProject();

	void printAccountSettings();
	void changeUsername();
	void changePassword();
	void deleteAccount(int &accountChoice);
	void accountSettings(int &accountChoice);
public:
	Interface(Storage &st, Session &se);
	void run();
};
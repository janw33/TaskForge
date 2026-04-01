#pragma once
#include "Storage.h"
#include "Session.h"

class Interface
{
	Storage &storage;
	Session &session;

	void printMenu();
	void signUp();
	void login();


	void printAccountMenu();

	void printProjectList();

	void printProjectMenu();
	void printTaskList();
	void printTaskMenu();
	void insideTask();
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
	bool deleteAccount();
	bool accountSettings();

	void accountMenu();
public:
	Interface(Storage &st, Session &se);
	void run();
};
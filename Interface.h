#pragma once
#include "Storage.h"
#include "Session.h"

class Interface
{
//=================================

//=========DATA====================
	Storage &storage;
	Session &session;
//=========LOGIN===================
	void printMenu();

	void signUp();
	void login();

//=========ACCOUNT=================
	void printAccountMenu();
	
	//show friend
	void printAccountsList();
	void printFriendsList();
	void showFriends();

	//add friend
	void addFriend();

	//delete friend
	void deleteFriend();

	//show projects
	void printProjectList();
	void insideProject();
	void showProjects();

	//add project
	void addProject();

	//delete project
	void deleteProject();

	//account settings
	void printMenuAccountSettings();
	void changeUsername();
	void changePassword();
	bool deleteAccount();
	bool accountSettings();

//=========PROJECT===================
	void printProjectMenu();

	//show tasks
	void printTaskList();
	void insideTask();
	void showTasks();

	//add task
	void addTask();
	
	//delete task
	void deleteTask();
//========TASK=======================
	void printTaskMenu();

//===================================

	void accountMenu();
public:
	Interface(Storage &st, Session &se);
	void run();
};
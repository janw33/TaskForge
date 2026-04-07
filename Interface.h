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
	void printAvailableAccountsList();
	void printFriendsList();
	void showFriends();

	//add friend
	void addFriend();

	//delete friend
	void deleteFriend();

	//show projects
	void printProjectList();
	void insideOwnerProject();
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

//---------Tasks---------------------
	//show tasks
	void printTaskList();
	void insideTask();
	void showTasks();

	//add task
	void addTask();
	
	//delete task
	void deleteTask();

//---------Users---------------------
	//show users
	bool alreadyInProject(std::uint64_t ID);
	bool printAvailableUsersList();
	bool printProjectMembers();

	//add user 
	void printAvailalbleUsersList();
	void addUser();

	//deleteUser
	void deleteUser();
	
//========TASK=======================
	void printTaskMenu();

//===================================

	void accountMenu();
public:
	Interface(Storage &st, Session &se);
	void run();
};
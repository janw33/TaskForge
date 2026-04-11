#pragma once
#include "Session.h"

class Interface
{
//=========DATA====================
	Session &session;
//=========LOGIN===================
	void printMenu();

	void signUp();
	void login();

//=========ACCOUNT=================
	void printAccountMenu();
	
	//show friend
	bool printAvailableAccountsList();
	bool printFriendsList();

	//add friend
	void addFriend();

	//delete friend
	void deleteFriend();

	//show projects
	void printProjectList();
	void insideUserProject();
	void insideAdminProject();
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
	void deleteAccount();
	void accountSettings();

//=========PROJECT===================
	void printUserProjectMenu();
	void printAdminProjectMenu();
	void printOwnerProjectMenu();

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
	Interface(Session &session);
	void run();
};
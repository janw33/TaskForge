#pragma once
#include "Session.h"

class Interface
{
//=========DATA====================
	Session &session;
//=========LOGIN=================== //done
	void printMenu();

	void signUp(); 
	void login(); 

//=========ACCOUNT================= //done
	void printAccountMenu();
	
	//show friend 
	bool printAvailableAccountsList();
	bool printFriendsList();

	//add friend
	void addFriend(); 

	//delete friend
	void deleteFriend(); 

	//show projects 
	bool printProjectList(); 
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

//---------Tasks--------------------- //done
	//show tasks
	bool printTaskList(); 
	void insideTask();
	void showTasks();

	//add task
	void addTask();
	
	//delete task
	void deleteTask();

//---------Users---------------------
	//show users
	bool printAvailableUsersList();
	bool printProjectMembers();

	//add user 
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
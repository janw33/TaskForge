#include <iostream>
#include <limits>
#include <unistd.h>
#include "Interface.h"

void Interface::printMenu()
{
    std::cout << "=================\n";
    std::cout << "       Menu      \n";
    std::cout << "=================\n";
    std::cout << "[1] Sign Up      \n";
    std::cout << "[2] Log In       \n";
    std::cout << "[3] Exit         \n";
}
void Interface::printAccountMenu()
{
	std::cout << "================= \n";
	std::cout << "  Account Menu    \n";
	std::cout << "================= \n";
	std::cout << "[1] Show Projects \n";
	std::cout << "[2] Add Project   \n";
	std::cout << "[3] Delete Project\n";
    std::cout << "[4] Settings      \n";
	std::cout << "[5] Log Out       \n";
}
void Interface::printAccountSettings()
{
    std::cout << "===================\n";
	std::cout << " Account Settings  \n";
	std::cout << "===================\n";
	std::cout << "[1] Change Username\n";
	std::cout << "[2] Change Password\n";
	std::cout << "[3] Delete Accoount\n";
	std::cout << "[4] Exit           \n";
}
void Interface::printProjectMenu()
{
    std::cout << "================= \n";
    std::cout << "  Project Menu    \n";
    std::cout << "================= \n";
    std::cout << "[1] Show Tasks    \n";
    std::cout << "[2] Add Task      \n";
    std::cout << "[3] Delete Task   \n";
    std::cout << "[4] Log Out       \n";
}


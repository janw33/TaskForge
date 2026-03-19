#include <iostream>
#include <limits>
#include "Interface.h"


void Interface::print(const std::string &message)
{
    std::cout << message << '\n';
}
std::string Interface::askString(const std::string& prompt)
{
    std::string input;

    std::cout << prompt;
    std::getline(std::cin, input);

    return input;
}



void Interface::printMenu()
{
    std::cout << "================\n";
    std::cout << "      Menu      \n";
    std::cout << "================\n";
    std::cout << "[1] Sign Up     \n";
    std::cout << "[2] Log In      \n";
    std::cout << "[3] Exit        \n";
}



void Interface::printAccountMenu()
{
	std::cout << "================\n";
	std::cout << "  Account Menu  \n";
	std::cout << "================\n";
	std::cout << "[1] Show Tasks  \n";
	std::cout << "[2] Add Task    \n";
	std::cout << "[3] Delete Task \n";
	std::cout << "[4] Exit        \n";
}



int Interface::getChoice(int min, int max)
{
    std::string input;

    while (true)
    {
        std::getline(std::cin, input);

        if (input.size() == 1 && input[0] >= '0' && input[0] <= '9')
        {
            int choice = input[0] - '0';

            if (choice >= min && choice <= max)
                return choice;
        }

        std::cout << "Invalid choice, please try again:\n";
    }
}



void Interface::pause()
{
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
void Interface::clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}
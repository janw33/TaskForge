#include <iostream>
#include <limits>
#include "Interface.h"

void Interface::print(const std::string &message)
{
    std::cout << message << '\n';
}


void Interface::printMenu()
{
	std::cout << "================\n";
	std::cout << "      Menu      \n";
	std::cout << "================\n";
	std::cout << "[1] Show Tasks  \n";
	std::cout << "[2] Add Task    \n";
	std::cout << "[3] Delete Task \n";
	std::cout << "[4] Exit        \n";
}
int Interface::getMenuChoice(const int min,const int max)
{
    int x;

    while (true)
    {
        std::cout << "Choose option (" << min << "-" << max << "): ";

        if (!(std::cin >> x))
        {
            std::cout << "You must enter a number!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (x < min || x > max)
        {
            std::cout << "Invalid option!\n";
            continue;
        }

        return x;
    }
}



std::string Interface::askName()
{
    std::string name;

    std::cout << "Enter name: \n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);

    return name;
}
std::string Interface::askPriority()
{
    std::string priority;

    std::cout << "Enter priority: \n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, priority);

    return priority;
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
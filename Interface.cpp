#include <iostream>
#include <limits>
#include <conio.h>
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

std::string Interface::askPassword(const std::string& prompt)
{
    std::cout << prompt;
    return inputPassword();
}



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
	std::cout << "[4] Log Out       \n";
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
    std::string tmp;
    std::getline(std::cin, tmp);
}

void Interface::clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

void Interface::pauseClear()
{
     pause();
    clearScreen();
}

void Interface::printPauseClear(std::string error)
{
    print(error);
    pause();
    clearScreen();
}



std::string Interface::inputPassword()
{
    std::string password;
    char c;

    const char ENTER = '\r';
    const char BACKSPACE = '\b';

    while ((c = _getch()) != ENTER)
    {
        if (c == 0 || c == 224)
        {
            _getch();
            continue;
        }

        if (c == BACKSPACE)
        {
            if (!password.empty())
            {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else
        {
            password += c;
            std::cout << "*";
        }
    }

    std::cout << "\n";
    return password;
}
#include <iostream>
#include "Interface.h"

Interface::Interface(AccountManager& am)
    : accountManager(am)
{
}

void Interface::printMenu()
{
    std::cout << "=================\n";
    std::cout << "       Menu      \n";
    std::cout << "=================\n";
    std::cout << "[1] Sign up      \n";
    std::cout << "[2] Log in       \n";
    std::cout << "[3] Exit         \n";
}

void Interface::signUp(bool &logged)
{
    while(true)
    {
        std::cout<<"Enter username: ";
        std::string username;
        std::getline(std::cin, username);
        std::cout<<'\n';
        if(accountManager.isUsernameTaken(username))
        {
            std::cout<<"Username is unavailable\n";
            continue;
        }
        //walidacja username

        std::cout<<"Enter password: ";
        std::string password;
        std::getline(std::cin, password);
        std::cout<<'\n';
        //walidacja password, hashowanie password
        accountManager.addAccount(username, password);
        std::cout <<"Signed up successfully\n";
        logged = true;
        return;
    }
}

void Interface::login(bool &logged)
{
    while(true)
    {
        std::cout<<"Enter username: ";
        std::string username;
        std::getline(std::cin, username);
        std::cout<<'\n';

        std::cout<<"Enter password: ";
        std::string password;
        std::getline(std::cin, password);
        std::cout<<'\n';

        if(!accountManager.login(username, password))
        {
            std::cout << "Credentials are invalid\n";
            continue;
        }

        std::cout << "Logged successfully\n";
        logged = true;
        return;
    }
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
    std::cout << "[3] Delete Account \n";
    std::cout << "[4] Exit           \n";
}

void Interface::changeUsername()
{
    while(true)
    {
        std::cout << "Enter new username\n";
        std::string newUsername;
        std::getline(std::cin, newUsername);

        if(accountManager.isUsernameTaken(newUsername))
        {
        std::cout<<"Username is unavailable\n";
        continue;
        }

        accountManager.changeUsername(newUsername);
        std::cout << "Username was changed successfully\n";
        return;
    }
}

void Interface::changePassword()
{
    std::cout << "Enter new password\n";
    std::string newPassword;
    std::getline(std::cin, newPassword);

    accountManager.changePassword(newPassword);
    std::cout << "Password was changed successfully\n";
}

void Interface::deleteAccount(int &accountChoice)
{
    accountManager.deleteAccount();
    std::cout << "Account was deleted successfully\n";
    accountChoice = 5;
}

void Interface::accountSettings(int &accountChoice)
{
    while (true)
    {
        printAccountSettings();
        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        int choice = stoi(choiceStr);

        switch(choice)
        {
        case 1: changeUsername(); break;
        case 2: changePassword(); break;
        case 3: deleteAccount(accountChoice); break;
        case 4: return;
        }
    }
}

void Interface::run() // dodaj walidacje choice
{
    while (true)
    {   
        bool logged = false;

        while(!logged)
        {
            printMenu();
            std::string choiceStr;
            std::getline(std::cin, choiceStr);
            int choice = stoi(choiceStr);

            switch (choice)
            {
                case 1: signUp(logged); break;
                case 2: login(logged); break;
                case 3: std::cout << "Goodbye\n"; return;
            }
        }

        int accountChoice = 0;

        while(accountChoice!=5)
        {
            printAccountMenu();
            std::string accountChoiceStr;
            std::getline(std::cin, accountChoiceStr);
            accountChoice = stoi(accountChoiceStr);

            switch(accountChoice)
            {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: accountSettings(accountChoice); break;
            case 5: accountManager.logout(); std::cout << "Log Out\n"; break;
            }
        }
    }
}
#include <iostream>
#include "Interface.h"

Interface::Interface(Storage &st, Session &se)
    : storage(st), session(se)
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

        if(storage.isUsernameTaken(username))
        {
            std::cout<<"Username is unavailable\n";
            session.logout();
            continue;
        }
        //walidacja username

        std::cout<<"Enter password: ";
        std::string password;
        std::getline(std::cin, password);
        std::cout<<'\n';

        //walidacja password, hashowanie password

        storage.addAccount(username, password);

        Account* acc = storage.findAccountByUsername(username);
        if(acc) session.setCurrentAccount(acc);
        else {
            std::cout << "Fatal Error";
            return;
        }

        std::cout <<"Signed up successfully\n";
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

        std::cout<<"Enter password: ";
        std::string password;
        std::getline(std::cin, password);

        if(!storage.validateCredentials(username, password))
        {
            std::cout << "Credentials are invalid\n";
            session.logout();
            continue;
        }

        Account* acc = storage.findAccountByUsername(username);
        if(acc) session.setCurrentAccount(acc);
        else {
            std::cout << "Fatal Error";
            return;
        }

        std::cout << "Logged successfully\n";
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

void Interface::printProjectList()
{
    for(const auto& project : session.getProjects())
    {
        std::cout <<"[" + std::to_string(project.getId()) + "] " + project.getName() + '\n';
    }
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
void Interface::showTasks()
{

}
void Interface::addTask()
{
    std::cout << "Enter name: ";
    std::string name;
    std::getline(std::cin, name);

    
}
void Interface::deleteTask()
{

}
void Interface::insideProject()
{
    while(true)
    {
        printProjectMenu();
        
        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        int choice = stoi(choiceStr);

        switch(choice)
        {
            case 1:
            case 2:
            case 3: 
            case 4: std::cout << "Goodbye\n"; return;
        }
    }
}
void Interface::showProjects()
{
    std::cout << "Enter project id: \n";

    printProjectList();

    std::string idStr;
    std::getline(std::cin, idStr);
    int id = stoi(idStr);

    Project* prj = session.findProjectByID(id);

    if(prj)
    {
        session.setCurrentProject(prj);
        insideProject();
        return;
    }

    std::cout << "Invalid id\n";
}
void Interface::addProject()
{
    std::cout << "Enter project name\n";
    std::string name;
    std::getline(std::cin, name);

    session.addProject(name);
    std::cout << "Project was added successfully\n";
    
}
void Interface::deleteProject()
{
    std::cout << "Enter project id: \n";

    printProjectList();

    std::string idStr;
    std::getline(std::cin, idStr);
    int id = stoi(idStr);

    std::ptrdiff_t index = session.findProjectIndexByID(id);

    if(index != -1)
    {
        session.deleteProject(index);
        std::cout << "Project was deleted successfully\n";
        return;
    }

    std::cout << "Invalid id\n";
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

        if(storage.isUsernameTaken(newUsername))
        {
        std::cout<<"Username is unavailable\n";
        continue;
        }

        session.changeUsername(newUsername);
        std::cout << "Username was changed successfully\n";
        return;
    }
}

void Interface::changePassword()
{
    std::cout << "Enter new password\n";
    std::string newPassword;
    std::getline(std::cin, newPassword);

    session.changePassword(newPassword);
    std::cout << "Password was changed successfully\n";
}

void Interface::deleteAccount(int &accountChoice)
{
    std::ptrdiff_t index = storage.findAccountIndexByUsername(session.getUsername());
    if(index == -1)
    {
        std::cout << "Fatal error\n";
        return;
    }
    storage.deleteAccount(index);
    session.logout();
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
            case 1: showProjects(); break;
            case 2: addProject(); break;
            case 3: deleteProject(); break;
            case 4: accountSettings(accountChoice); break;
            case 5: session.logout(); std::cout << "Log Out\n"; break;
            }
        }
    }
}
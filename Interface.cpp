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

void Interface::signUp()
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

void Interface::login()
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
    if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
    }

    for(const auto& project : session.getProjects()) std::cout <<"[" + std::to_string(project.getID()) + "] " + project.getName() + '\n';
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
void Interface::printTaskList()
{
    if(!session.isProjectOpened()) {
        std::cout << "Error\n";
        return;
    }

    for(const auto& Task : session.getTasks()) {
        if(Task.getIsDone()) std::cout << "[" + std::to_string(Task.getID()) + "] " + Task.getName() + " " + "DONE" + '\n';
        else std::cout << "[" + std::to_string(Task.getID()) + "] " + Task.getName() + " " + "UNDONE" + '\n';
    }
}
void Interface::printTaskMenu(){
    std::cout << "================= \n";
    std::cout << "   Task Menu      \n";
    std::cout << "================= \n";
    std::cout << "[1] Done/Undone   \n";
    std::cout << "[2] Settings      \n";
    std::cout << "[3] Exit          \n";
}
void Interface::insideTask() {
    if(!session.isTaskOpened()) {
        std::cout << "Error\n";
        return;
    }

    while(true)
    {
        printTaskMenu();
        
        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        int choice = stoi(choiceStr);

        switch(choice)
        {
            case 1:
            session.changeTaskStatus();
            if (session.getIsDone() == true) std::cout << "Task is done\n";
            else std::cout << "Task id Undone\n";
            break;

            case 2: break; // no setting for now!
            case 3: std::cout << "Goodbye\n"; session.exitTask(); return;
        }
    }
}
void Interface::showTasks()
{
    if(!session.isProjectOpened()) {
        std::cout << "Error\n";
        return;
    }

    if(session.getTasks().empty())
    {
        std::cout << "Project has no tasks\n";
        return;
    }
    std::cout << "Enter ID:\n";

    printTaskList();

    std::string choiceStr;
    std::getline(std::cin, choiceStr);
    std::uint64_t choice = std::stoull(choiceStr);

    Task* tsk = session.findTaskByID(choice);

    if(!tsk)
    {
        std::cout << "Invalid id\n";
        return;
    }

    session.setCurrentTask(tsk);
    insideTask();
    session.exitTask();
}
void Interface::addTask()
{
    if(!session.isProjectOpened()) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter name: ";
    std::string name;
    std::getline(std::cin, name);

    session.addTask(name);
    std::cout << "Task was added successfully\n";
}
void Interface::deleteTask()
{
    if(!session.isProjectOpened()) {
        std::cout<< "Error\n";
        return;
    }

    std::cout << "Enter ID:\n";

    printTaskList();

    std::string choiceStr;
    std::getline(std::cin, choiceStr);
    std::uint64_t choice = std::stoull(choiceStr);

    if(!session.deleteTask(choice))
    {
        std::cout << "Invalid ID\n";
        return;
    }

    std::cout<<"Task was deleted successfully\n";
}
void Interface::insideProject()
{
    if(!session.isProjectOpened()) {
        std::cout << "Error\n";
        return;
    }

    while(true)
    {
        printProjectMenu();
        
        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        int choice = stoi(choiceStr);

        switch(choice)
        {
            case 1: showTasks(); break;
            case 2: addTask(); break;
            case 3: deleteTask(); break;
            case 4: std::cout << "Goodbye\n"; session.exitProject(); return;
        }
    }
}
void Interface::showProjects()
{
    if(!session.isAccountOpened()) {
        std::cout << "Errro\n";
        return;
    }

    if(session.getProjects().empty())
    {
        std::cout << "You have zero projects\n";
        return;
    }
    
    std::cout << "Enter project id: \n";

    printProjectList();

    std::string idStr;
    std::getline(std::cin, idStr);
    int id = stoi(idStr);

    Project* prj = session.findProjectByID(id);

    if(!prj)
    {
        std::cout << "Invalid id\n";
        return;
    }

    session.setCurrentProject(prj);
    insideProject();
    session.exitProject();
}
void Interface::addProject()
{
    if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter project name\n";
    std::string name;
    std::getline(std::cin, name);

    session.addProject(name);
    std::cout << "Project was added successfully\n";
    
}
void Interface::deleteProject()
{

    if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter project id: \n";

    printProjectList();

    std::string idStr;
    std::getline(std::cin, idStr);
    std::uint64_t id = stoi(idStr);

    if(!session.deleteProject(id))
    {
        std::cout << "Invalid ID\n";
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
    if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
    }

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
    if(session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter new password\n";
    std::string newPassword;
    std::getline(std::cin, newPassword);

    session.changePassword(newPassword);
    std::cout << "Password was changed successfully\n";
}

bool Interface::deleteAccount()
{

    if(!storage.deleteAccount(session.getAccountID()))
    {
        std::cout << "Fatal error\n";
        return false;
    }

    std::cout << "Account was deleted successfully\n";
    return true;
}

bool Interface::accountSettings()
{
    if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return false;
    }

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
        case 3: if(deleteAccount()) return true; break;
        case 4: std::cout<<"Goodbye\n"; return false;
        }
    }
}

void Interface::accountMenu(){
     if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
     }

     while(true)
        {
            printAccountMenu();
            std::string accountChoiceStr;
            std::getline(std::cin, accountChoiceStr);
            int accountChoice = stoi(accountChoiceStr);

            switch(accountChoice)
            {
            case 1: showProjects(); break;
            case 2: addProject(); break;
            case 3: deleteProject(); break;

            case 4: 
            if(accountSettings()){
                session.logout();
                return;
            } 
            break;

            case 5: session.logout(); std::cout << "Log Out\n"; return;
            }
        }
}
void Interface::run() 
{
    while (true)
    {   
        while(!session.isLogged())
        {
            printMenu();
            std::string choiceStr;
            std::getline(std::cin, choiceStr);
            int choice = stoi(choiceStr);

            switch (choice)
            {
                case 1: signUp(); break;
                case 2: login(); break;
                case 3: std::cout << "Goodbye\n"; return;
            }
        }

        accountMenu();
    }
}
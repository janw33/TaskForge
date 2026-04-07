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

        Account* acc = storage.signUp(username, password);

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

        Account* acc = storage.logIn(username, password);
        if(acc) session.setCurrentAccount(acc);
        else {
            std::cout << "Invalid Credentials";
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
    std::cout << "[1] Show Friends  \n";
    std::cout << "[2] Add Friend    \n";
    std::cout << "[3] Delete Friend \n";
    std::cout << "[4] Show Projects \n";
    std::cout << "[5] Add Project   \n";
    std::cout << "[6] Delete Project\n";
    std::cout << "[7] Settings      \n";
    std::cout << "[8] Log Out       \n";
}

void Interface::printAvailableAccountsList() {
    if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
    }

    for (size_t i = 0; i < storage.getAccounts().size(); i++) {

        auto& account = storage.getAccounts()[i];

        if (account.getID() == session.getAccountID()) continue;

        bool isFriend = false;
        for (size_t j = 0; j < session.getFriendsIDs().size(); j++) {
            if (session.getFriendsIDs()[j] == account.getID()) {
                isFriend = true;
                break;
            }
        }

        if (!isFriend) {
            std::cout << "[" + std::to_string(account.getID()) + "] " + account.getUsername() + '\n';
        }
    }
}
void Interface::printFriendsList() {
    if(!session.isAccountOpened()) {
        std::cout <<"Error\n";
        return;
    }

    const auto &friends = session.getFriendsIDs();

    if(friends.empty()) {
        std::cout << "You have zero friends\n";
        return;
    }

    for(auto id : friends) {
    Account* f = storage.findAccountByID(id);
    if(f) std::cout << "[" + std::to_string(f->getID()) + "] " + f -> getUsername() + '\n';
    }
}
void Interface::showFriends(){
    if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
    }

    printFriendsList();
}

void Interface::addFriend(){
    if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter friend ID\n";

    printAvailableAccountsList();

    std::string friendIDStr;
    std::getline(std::cin, friendIDStr);
    std::uint64_t friendID = std::stoull(friendIDStr);

    if(session.isHeMyFriend(friendID)) {
        std::cout << "Error\n";
        return;
    }
    if(!storage.addFriend(session.getAccountID(), friendID)){
        std::cout << "Error\n";
        return;
    }
    
    std::cout << "Friend added successfully\n";
}

void Interface::deleteFriend(){
    if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter friend ID\n";

    printFriendsList();

    std::string friendIDStr;
    std::getline(std::cin, friendIDStr);
    std::uint64_t friendID = std::stoull(friendIDStr);

    if(!session.isHeMyFriend(friendID)) {
        std::cout << "Error\n";
        return;
    }
    if(!storage.deleteFriend(session.getAccountID(), friendID)){
        std::cout << "Error\n";
        return;
    }

    std::cout << "Friend deleted successfully\n";
}

void Interface::printOwnerProjectMenu()
{
    std::cout << "================= \n";
    std::cout << "  Project Menu    \n";
    std::cout << "================= \n";
    std::cout << "[1] Show Tasks    \n";
    std::cout << "[2] Add Task      \n";
    std::cout << "[3] Delete Task   \n";
    std::cout << "[4] Show Users   \n";
    std::cout << "[5] Add User      \n";
    std::cout << "[6] Delete User   \n";
    std::cout << "[7] Exit          \n";
}
void Interface::printProjectList()
{
    if(!session.isAccountOpened()) {
        std::cout << "Error\n";
        return;
    }

    for(const auto& project : session.getProjects()) std::cout <<"[" + std::to_string(project.getID()) + "] " + project.getName() + '\n';
}
void Interface::printUserProjectMenu() {
    std::cout << "================= \n";
    std::cout << "   Project Menu   \n";
    std::cout << "================= \n";
    std::cout << "[1] Show Tasks    \n";
    std::cout << "[2] Show Users    \n";
    std::cout << "[3] Exit          \n";
}
void Interface::insideUserProject() {
    if(!session.isProjectOpened()) {
        std::cout << "Error\n" ;
        return;
    }

    while(true) {
        printUserProjectMenu();

        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        int choice = stoi(choiceStr);

        switch(choice) {
            case 1: showTasks(); break;
            case 2: printProjectMembers(); break;
            case 3: std::cout << "Goodbye"; session.exitProject(); return;
        }
    }
}
void Interface::printAdminProjectMenu() {
    std::cout << "================= \n";
    std::cout << "  Project Menu    \n";
    std::cout << "================= \n";
    std::cout << "[1] Show Tasks    \n";
    std::cout << "[2] Add Task      \n";
    std::cout << "[3] Delete Task   \n";
    std::cout << "[4] Show Users   \n";
    std::cout << "[5] Exit          \n";
}
void Interface::insideAdminProject() {
       if(!session.isProjectOpened()) {
        std::cout << "Error\n" ;
        return;
    }

    while(true) {
        printAdminProjectMenu();

        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        int choice = stoi(choiceStr);

        switch(choice) {
            case 1: showTasks(); break;
            case 2: addTask(); break;
            case 3: deleteTask(); break;
            case 4: printProjectMembers(); break;
            case 5: std::cout << "Goodbye\n"; session.exitProject(); return;
        }
    }
}

void Interface::insideOwnerProject()
{
    if(!session.isProjectOpened()) {
        std::cout << "Error\n";
        return;
    }

    while(true)
    {
        printOwnerProjectMenu();
        
        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        int choice = stoi(choiceStr);

        switch(choice)
        {
            case 1: showTasks(); break;
            case 2: addTask(); break;
            case 3: deleteTask(); break;
            case 4: printProjectMembers(); break;
            case 5: addUser(); break;
            case 6: deleteUser(); break;
            case 7: std::cout << "Goodbye\n"; session.exitProject(); return;
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
    std::uint64_t id = std::stoull(idStr);

    Project* prj = session.findProjectByID(id);

    if(!prj)
    {
        std::cout << "Invalid id\n";
        return;
    }

    session.setCurrentProject(prj);

    ProjectMember* member = session.findMemberByID(session.getAccountID());

    if(!member) {
        std::cout <<"Fatal error\n";
        return;
    }

    switch(member -> getRole()) {
        case Role::USER : insideUserProject(); break;
        case Role::ADMIN : insideAdminProject(); break;
        case Role::OWNER : insideOwnerProject(); break;
    }
    
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

    std::cout << "Project deleted successfully\n";
}

bool Interface::alreadyInProject(std::uint64_t ID) {
     for(const auto& member : session.getProjectMembers()){
        if (ID == member.getID()) {
            return true;
        }
    }
    return false;
}
bool Interface::printAvailableUsersList() {
    if(!session.isProjectOpened()) {
        std::cout << "Error\n";
        return false;
    }

    const auto &friends = session.getFriendsIDs();

    if(friends.empty()) {
        std::cout << "You have zero friends\n";
        return false;
    }

    for(auto ID : friends) {
    if(!alreadyInProject(ID)) {
    Account* f = storage.findAccountByID(ID);
    if(f) std::cout << "[" << f->getID() << "] " << f -> getUsername() << '\n'; }
    }

    return true;
}
bool Interface::printProjectMembers() {
    if(!session.isProjectOpened()) {
        std::cout<<"Error\n";
        return false;
    }
    
    if(session.getProjectMembers().empty()) {
        std::cout << "There is zero project members\n";
        return false;
    }

    for(const auto& member : session.getProjectMembers()) {
        std::cout << "[" << member.getID() << "] " << member.getUsername() << " " << member.roleToString() << '\n';
    }

    return true;
}

void Interface::addUser() {
    if(!session.isProjectOpened()) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter friend ID\n";

    if(!printAvailableUsersList()) {
        return;
    }

    std::string friendIDStr;
    std::getline(std::cin, friendIDStr);
    std::uint64_t friendID = std::stoull(friendIDStr);

    const auto& acc = storage.findAccountByID(friendID);
    if(!acc || alreadyInProject(friendID)) {std::cout << "Invalid ID\n"; return;}

    std::cout << "Which role has this user? (USER/ADMIN)\n";
    std::string input;
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin() , ::toupper);

    if(input == "USER") {
        storage.addProject(friendID, session.getProjectName(), Role::USER); 
        session.addMember(friendID, acc->getUsername(), Role::USER); }
    else if(input == "ADMIN") {
            storage.addProject(friendID, session.getProjectName(), Role::ADMIN);
            session.addMember(friendID, acc->getUsername(), Role::ADMIN); } 
    else {
         std::cout<<"Invalid Input"; return; }

    std::cout<<"User added successfully\n";
}   

void Interface::deleteUser(){
    if(!session.isProjectOpened()) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter friend ID\n";

    if(!printProjectMembers()) return;

    std::string friendIDStr;
    std::getline (std::cin, friendIDStr);
    std::uint64_t friendID = std::stoull(friendIDStr);

    ProjectMember* member = session.findMemberByID(friendID);

    if(session.getAccountID() == friendID || !member || member -> getRole() == Role::OWNER || !session.deleteMember(friendID)) {
        std::cout << "Invalid ID\n";
        return;
    }

    std::cout << "Member deleted successfully\n";
}

void Interface::printMenuAccountSettings()
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
    if(!session.isAccountOpened()) {
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
        printMenuAccountSettings();
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

void Interface::printTaskMenu(){
    std::cout << "================= \n";
    std::cout << "   Task Menu      \n";
    std::cout << "================= \n";
    std::cout << "[1] Done/Undone   \n";
    std::cout << "[2] Settings      \n";
    std::cout << "[3] Exit          \n";
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
            case 1: showFriends(); break;
            case 2: addFriend(); break;
            case 3: deleteFriend(); break;
            case 4: showProjects(); break;
            case 5: addProject(); break;
            case 6: deleteProject(); break;

            case 7: 
            if(accountSettings()){
                session.logout();
                return;
            } 
            break;

            case 8: session.logout(); std::cout << "Log Out\n"; return;
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
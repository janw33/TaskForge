#include <iostream>
#include "Interface.h"

Interface::Interface(Session &session)
    : session(session)
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

        std::cout<<"Enter password: ";
        std::string password;
        std::getline(std::cin, password);

        switch(session.signUp(username, password))
        {
            case RegisterResult::SUCCESS : std::cout << "Signed up successfully\n"; return;
            case RegisterResult::USERNAME_TAKEN : std::cout << "This useranem is already taken. Please, try again\n"; break;
        }
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

        switch(session.login(username, password)) {
            case LoginResult::SUCCESS : std::cout << "Logged in successfully\n"; return;
            case LoginResult::INVALID_USERNAME : std::cout << "Username is wrong"; break;
            case LoginResult::INVALID_PASSWORD : std::cout << "Password is wrong"; break;
        }
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

bool Interface::printFriendsList() {

    auto friends = session.getCurrentUserFriends();

    if(friends.empty()) {
        std::cout << "You have zero friends\n";
        return false;
    }

    std::cout << "Enter friend ID\n";
    for(auto f : friends) std::cout << "[" << f->getID() << "] " << f -> getUsername() << '\n';
    return true;
}

bool Interface::printAvailableAccountsList() {

    auto availableAccounts = session.getAvailableAccounts();

    if(availableAccounts.empty()) {
        std::cout << "There is no available account\n";
        return false;
    }

    std::cout << "Enter friend ID\n";
    for(auto acc : availableAccounts) std::cout << "[" << acc.getID() << "] " << acc.getUsername() << '\n';
    return true;
}

void Interface::addFriend(){
    if(!printAvailableAccountsList()) {
        return;
    }

    std::string IDStr;
    std::getline(std::cin, IDStr);
    std::uint64_t ID = std::stoull(IDStr);

    switch(session.addFriend(ID)) {
        case AddFriendResult::SUCCESS : std::cout<<"Friend added successfully\n"; break;
        case AddFriendResult::INVALID_ID : std::cout<<"Invalid ID\n"; break;
        case AddFriendResult::ALREADY_YOUR_FRIEND : std::cout << "You cannot add your friend again\n"; break;
        case AddFriendResult::CANNOT_ADD_SELF : std::cout << "You cannon add yourself\n"; break;
    }
}

void Interface::deleteFriend(){
    if(!printFriendsList()) return;

    std::string IDStr;
    std::getline(std::cin, IDStr);
    std::uint64_t ID = std::stoull(IDStr);

    switch(session.deleteFriend(ID)) {
        case DeleteFriendResult::SUCCESS : std::cout<<"Friend added successfully\n"; break;
        case DeleteFriendResult::INVALID_ID : std::cout<<"Invalid ID\n"; break;
        case DeleteFriendResult::NOT_FRIEND : std::cout<<"This is not your friend\n"; break;
        case DeleteFriendResult::CANNOT_DELETE_SELF : std::cout<<"You cannont delete yourself\n"; break;
    }
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
bool Interface::printProjectList()
{
    auto projects = session.getCurrentUserProjects();

    if(projects.empty()) {
        std::cout << "You have zero projects\n";
        return false;
    }

    std::cout << "Enter project ID: \n";
    for(auto project : projects) std::cout << "[" << project -> getID() << "] " << project -> getName() << '\n';
    return true;
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
    printProjectList();

    std::string IDStr;
    std::getline(std::cin, IDStr);
    std::uint64_t ID = std::stoull(IDStr);

    switch(session.openProject(ID)) {
        case OpenProjectResult::OWNER : printOwnerProjectMenu(); break;
        case OpenProjectResult::ADMIN : printAdminProjectMenu(); break; 
        case OpenProjectResult::USER : printUserProjectMenu(); break;
        case OpenProjectResult::INVALID_ID : std::cout << "Invalid ID\n"; break;
    }
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
    if(!printProjectList()) return;

    std::string IDStr;
    std::getline(std::cin, IDStr);
    std::uint64_t ID = std::stoull(IDStr);

    switch(session.deleteProject(ID)) {
        case DeleteProjectResult::SUCCESS : std::cout << "Project deleted successfully\n"; break;
        case DeleteProjectResult::INVALID_ID : std::cout << "Invalid ID\n"; break;
        case DeleteProjectResult::NO_PERMISSION : std::cout << "You have no permission to delete this project\n"; break;
    }
}

bool Interface::alreadyInProject(std::uint64_t ID) {
    auto currentProject = session.getCurrentProject();
    if(!currentProject) {
        std::cout << "Error\n";
        return false;
    }

     for(const auto& member : currentProject -> getProjectMembers()){
        if (ID == member.getID()) {
            return true;
        }
    }
    return false;
}
bool Interface::printAvailableUsersList() {
    auto currentAccount = session.getCurrentAccount();
    if(!currentAccount) {
        std::cout << "Error\n";
        return false;
    }

    const auto &friends = currentAccount -> getFriendsIDs();

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
    auto currentProject = session.getCurrentProject();
    if(!currentProject) {
        std::cout << "Error\n";
        return false;
    }
    
    const auto& members = currentProject -> getProjectMembers();

    if(members.empty()) {
        std::cout << "There is zero project members\n";
        return false;
    }

    for(const auto& member : members) {
        auto acc = storage.findAccountByID(member.getID());
        std::cout << "[" << acc -> getID() << "] " << acc -> getUsername() << " " << member.roleToString() << '\n';
    }

    return true;
}

void Interface::addUser() {
    auto currentProject = session.getCurrentProject();
    if(!currentProject) {
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

    auto acc = storage.findAccountByID(friendID);
    if(!acc || alreadyInProject(friendID)) {std::cout << "Invalid ID\n"; return;}

    std::cout << "Which role has this user? (USER/ADMIN)\n";
    std::string input;
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin() , ::toupper);

    if(input == "USER") {
        acc -> addProjectID(currentProject -> getID());
        session.addMember(friendID, Role::USER); }
    else if(input == "ADMIN") {
        acc -> addProjectID(currentProject -> getID());
        session.addMember(friendID, Role::ADMIN); } 
    else {
         std::cout<<"Invalid Input"; return; }

    std::cout<<"User added successfully\n";
}   

void Interface::deleteUser(){
     auto currentAccount = session.getCurrentAccount();
    if(!currentAccount) {
        std::cout << "Error\n";
        return;
    }


    std::cout << "Enter friend ID\n";

    if(!printProjectMembers()) return;

    std::string friendIDStr;
    std::getline (std::cin, friendIDStr);
    std::uint64_t friendID = std::stoull(friendIDStr);

    ProjectMember* member = session.findMemberByID(friendID);

    if(currentAccount -> getID() == friendID || !member || member -> getRole() == Role::OWNER || !session.deleteMember(friendID)) {
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
    while(true)
    {
        std::cout << "Enter new username\n";
        std::string newUsername;
        std::getline(std::cin, newUsername);

        switch(session.changeUsername(newUsername)) {
            case ChangeUsernameResult::SUCCESS : std::cout << "Username was changed successfully\n"; return;
            case ChangeUsernameResult::USERNAME_TAKEN : std::cout << "This useranem is already taken. Please, try again\n"; break;
            case ChangeUsernameResult::SAME_AS_OLD : std::cout << "New username must be different from the current one\n"; break;
        }
    }
}
void Interface::changePassword()
{
    while(true) {
        std::cout << "Enter new password\n";
        std::string newPassword;
        std::getline(std::cin, newPassword);

        switch(session.changePassword(newPassword)) {
            case ChangePasswordResult::SUCCESS : std::cout << "Password was changed successfully\n"; return;
            case ChangePasswordResult::SAME_AS_OLD : std::cout << "New password must be different from the current one\n"; break;
        }
    }
}
void Interface::deleteAccount()
{
    switch(session.deleteAccount()) {
        case DeleteAccountResult::SUCCESS : std:: cout << "Account was delteted successfully\n"; return;
    }
}
void Interface::accountSettings()
{
    while (session.isLogged())
    {
        printMenuAccountSettings();
        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        int choice = stoi(choiceStr);

        switch(choice)
        {
        case 1: changeUsername(); break;
        case 2: changePassword(); break;
        case 3: deleteAccount(); break;
        case 4: std::cout<<"Goodbye\n"; return;
        }
    }
}

bool Interface::printTaskList()
{
    auto tasks = session.getCurrentProjectTasks();

    if(tasks.empty()){
        std::cout << "Project has no tasks\n";
        return false;
    }

    std::cout << "Enter Task ID\n";
    for(const auto& task : tasks) {
        if(task.getIsDone()) std::cout << "[" << task.getID() << "] " << task.getName() << " DONE" << '\n';
        else std::cout << "[" << task.getID() << "] " << task.getName() << " UNDONE" << '\n';
    }
    return true;
}
void Interface::insideTask() {
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
    if(!printTaskList()) return;

    std::string IDStr;
    std::getline(std::cin, IDStr);
    std::uint64_t ID = std::stoull(IDStr);

    switch(session.openTask(ID)) {
        case OpenTaskResult::SUCCESS : insideTask(); break;
        case OpenTaskResult::INVALID_ID : std::cout<<"Invalid ID\n"; break;
    }
}

void Interface::addTask()
{
    std::cout << "Enter name: ";
    std::string name;
    std::getline(std::cin, name);

    session.addTask(name);
    std::cout << "Task was added successfully\n";
}
void Interface::deleteTask()
{
    if(!printTaskList()) return;

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
     while(session.isLogged())
        {
            printAccountMenu();
            std::string accountChoiceStr;
            std::getline(std::cin, accountChoiceStr);
            int accountChoice = stoi(accountChoiceStr);

            switch(accountChoice)
            {
            case 1: printFriendsList(); break;
            case 2: addFriend(); break;
            case 3: deleteFriend(); break;
            case 4: showProjects(); break;
            case 5: addProject(); break;
            case 6: deleteProject(); break;
            case 7: accountSettings(); break;
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
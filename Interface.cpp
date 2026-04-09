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
            std::cout << "Invalid Credentials\n";
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

bool Interface::printFriendsList() {
    auto currentAccount = session.getCurrentAccount();
    if (!currentAccount) {
        std::cout << "Error\n";
        return false;
    }

    const auto &friends = currentAccount -> getFriendsIDs();

    if(friends.empty()) {
        std::cout << "You have zero friends\n";
        return false;
    }

    for(auto friendID : friends) {
    Account* f = storage.findAccountByID(friendID);
    if(f) std::cout << "[" << f->getID() << "] " << f -> getUsername() << '\n';
    }

    return true;
}

bool Interface::printAvailableAccountsList() {
    auto currentAccount = session.getCurrentAccount();
    if (!currentAccount) {
        std::cout << "Error\n";
        return false;
    }

    const auto& friends = currentAccount->getFriendsIDs();

    bool foundAny = false;

    for (const auto& account : storage.getAccounts()) {

        if (account.getID() == currentAccount->getID()) continue;

        bool isFriend = false;

        for (auto friendID : friends) {
            if (friendID == account.getID()) {
                isFriend = true;
                break;
            }
        }

        if (!isFriend) {
            foundAny = true;
            std::cout << "[" << account.getID() << "] " << account.getUsername() << '\n';
        }
    }
    if(!foundAny) {
        std::cout << "There is no more accounts\n";
        return false;
    }

    return true;
}

void Interface::addFriend(){
    auto currentAccount = session.getCurrentAccount();
    if (!currentAccount) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter friend ID\n";

    if(!printAvailableAccountsList()) {
        return;
    }

    std::string friendIDStr;
    std::getline(std::cin, friendIDStr);
    std::uint64_t friendID = std::stoull(friendIDStr);

    if(currentAccount->getID()==friendID || session.isHeMyFriend(friendID) || !storage.addFriend(currentAccount->getID(), friendID)){
        std::cout << "Invalid ID\n";
        return;
    }
    
    std::cout << "Friend added successfully\n";
}

void Interface::deleteFriend(){
    auto currentAccount = session.getCurrentAccount();
    if (!currentAccount) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter friend ID\n";

    if(!printFriendsList()) return;

    std::string friendIDStr;
    std::getline(std::cin, friendIDStr);
    std::uint64_t friendID = std::stoull(friendIDStr);

    if(currentAccount->getID()==friendID || !session.isHeMyFriend(friendID) || !storage.deleteFriend(currentAccount->getID(), friendID)){
        std::cout << "Invalid ID\n";
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
    auto currentAccount = session.getCurrentAccount();
    if (!currentAccount) {
        std::cout << "Error\n";
        return;
    }

    for(auto projectID : currentAccount->getProjectsIDs()) {
        auto project = storage.findProjectByID(projectID);
        if(project) std::cout <<"[" << project -> getID() << "] " << project -> getName() << '\n'; 
    }
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
    auto currentAccount = session.getCurrentAccount();
    if (!currentAccount) {
        std::cout << "Error\n";
        return;
    }

    if(currentAccount -> getProjectsIDs().empty())
    {
        std::cout << "You have zero projects\n";
        return;
    }
    
    std::cout << "Enter project id: \n";

    printProjectList();

    std::string idStr;
    std::getline(std::cin, idStr);
    std::uint64_t id = std::stoull(idStr);

    Project* prj = storage.findProjectByID(id);

    if(!prj)
    {
        std::cout << "Invalid id\n";
        return;
    }

    session.setCurrentProject(prj);

    ProjectMember* member = session.findMemberByID(currentAccount -> getID());

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
    auto currentAccount = session.getCurrentAccount();
    if (!currentAccount) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Enter project name\n";
    std::string name;
    std::getline(std::cin, name);

    std::uint64_t projectID = storage.addProject(name, currentAccount -> getID(), Role::OWNER);
    session.addProjectID(projectID);
    std::cout << "Project was added successfully\n";
}

void Interface::deleteProject()
{
    std::cout << "Enter project id: \n";

    printProjectList();

    std::string idStr;
    std::getline(std::cin, idStr);
    std::uint64_t id = stoi(idStr);

    auto currentAccount = session.getCurrentAccount();
    if(!currentAccount) {
        std::cout << "Error\n";
        return;
    }

    auto currentProject = session.getCurrentProject();
    if(!currentProject) {
        std::cout << "Error\n";
        return;
    } 
    
    auto currentMember = currentProject -> findMemberByID(currentAccount -> getID());
    if(!currentMember) {
        std::cout <<"Error\n";
        return;
    }

    if(currentMember -> getRole() != Role::OWNER) {
        std::cout << "You have no permission to delete this project\n";
        return;
    }
    if(!session.deleteProjectID(id))
    {
        std::cout << "Invalid ID\n";
        return;
    }
    if(!storage.deleteProject(id)) {
        std::cout << "Error\n";
        return;
    }

    std::cout << "Project deleted successfully\n";
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
bool Interface::deleteAccount()
{
    auto currentAccount = session.getCurrentAccount();
    if(!currentAccount) {
        std::cout << "Error\n";
        return false;
    }

    if(!storage.deleteAccount(currentAccount -> getID()))
    {
        std::cout << "Fatal error\n";
        return false;
    }

    std::cout << "Account was deleted successfully\n";
    return true;
}
bool Interface::accountSettings()
{
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
    auto currentProject = session.getCurrentProject();
    if(!currentProject) {
        std::cout << "Error\n";
        return;
    }

    for(const auto& Task : currentProject -> getTasks()) {
        if(Task.getIsDone()) std::cout << "[" + std::to_string(Task.getID()) + "] " + Task.getName() + " " + "DONE" + '\n';
        else std::cout << "[" + std::to_string(Task.getID()) + "] " + Task.getName() + " " + "UNDONE" + '\n';
    }
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
    auto currentProject = session.getCurrentProject();
    if(!currentProject) {
        std::cout << "Error\n";
        return;
    }

    if(currentProject -> getTasks().empty())
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
    std::cout << "Enter name: ";
    std::string name;
    std::getline(std::cin, name);

    session.addTask(name);
    std::cout << "Task was added successfully\n";
}
void Interface::deleteTask()
{
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
     while(true)
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
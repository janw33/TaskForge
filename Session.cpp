#include "Session.h"

Session::Session(Storage &storage)
    :storage(storage), currentAccountID(0), currentProjectID(0), currentTaskID(0)
{
}



RegisterResult Session::signUp(const std::string &username, const std::string &password) {
    if(storage.isUsernameTaken(username)) return RegisterResult::USERNAME_TAKEN;

    auto newAccountID = storage.addAccount(username, password);

    currentAccountID = newAccountID;

    return RegisterResult::SUCCESS;
}

LoginResult Session::login(const std::string &username, const std::string &password) {
    std::uint64_t ID = storage.findAccountIDByUsername(username);

    if(ID == 0) return LoginResult::INVALID_USERNAME;

    Account* acc = storage.findAccountByID(ID);
    assert(acc);

    if(acc -> getPassword() != password) return LoginResult::INVALID_PASSWORD;

    currentAccountID = ID;
    return LoginResult::SUCCESS;
}



ChangeUsernameResult Session::changeUsername(const std::string &newUsername) {
    assert(currentAccountID != 0 && "No user logged in!");

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);

    if(currentAccount -> getUsername() == newUsername) return ChangeUsernameResult::SAME_AS_OLD;
    if(storage.isUsernameTaken(newUsername)) return ChangeUsernameResult::USERNAME_TAKEN;

    currentAccount->setUsername(newUsername);
    return ChangeUsernameResult::SUCCESS;
}

ChangePasswordResult Session::changePassword(const std::string &newPassword) {
    assert(currentAccountID != 0 && "No user logged in!");

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);

    if(currentAccount -> getPassword() == newPassword) return ChangePasswordResult::SAME_AS_OLD;

    currentAccount->setPassword(newPassword);
    return ChangePasswordResult::SUCCESS;
}

DeleteAccountResult Session::deleteAccount() {
    assert(currentAccountID != 0 && "No user logged in!");

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);
    
    auto projects = currentAccount->getProjectsIDs();

    for(auto projectID : projects) {
        Project* prj = storage.findProjectByID(projectID);
        if(!prj) continue;

        ProjectMember* member = prj -> findMemberByID(currentAccount -> getID());
        if(!member) continue;

        if(member -> getRole() == Role::OWNER) storage.deleteProject(projectID);
            else prj -> deleteMember(currentAccount -> getID());
    }

    storage.deleteAccount(currentAccount -> getID(), currentAccount -> getUsername());
    logout();
    return DeleteAccountResult::SUCCESS;
}



std::vector<Account> Session::getAvailableAccounts() const {
    assert(currentAccountID != 0 && "No user logged in!");

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);

    std::vector <Account> result;

    const auto& friends = currentAccount->getFriendsIDs();

    for (const auto& [id, acc] : storage.getAccounts()) {

        if (id == currentAccount->getID()) continue;

        bool isFriend = false;

        for (auto friendID : friends) {
            if (friendID == acc.getID()) {
                isFriend = true;
                break;
            }
        }

        if (!isFriend) result.push_back(acc);
    }
    return result;
}

std::vector<Account*> Session::getCurrentUserFriends() const {
    assert(currentAccountID != 0 && "No user logged in!");

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);

    std::vector <Account*> result;

    for(auto friendID : currentAccount -> getFriendsIDs()) {
        auto f = storage.findAccountByID(friendID);
        if (f) result.push_back(f); 
    }

    return result;
}

AddFriendResult Session::addFriend(std::uint64_t ID) {
    assert(currentAccountID != 0 && "No user logged in!");

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);

    if(ID == currentAccount -> getID()) return AddFriendResult::CANNOT_ADD_SELF;

    Account* friendAccount = storage.findAccountByID(ID);

    if(!friendAccount) return AddFriendResult::INVALID_ID;
    if(currentAccount -> isHeMyFriend(ID)) return AddFriendResult::ALREADY_YOUR_FRIEND;

    currentAccount -> addFriend(ID);
    friendAccount -> addFriend(currentAccount -> getID());
    return AddFriendResult::SUCCESS;
}

DeleteFriendResult Session::deleteFriend(std::uint64_t ID) {
    assert(currentAccountID != 0 && "No user logged in!");

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);

    if(ID == currentAccount -> getID()) return DeleteFriendResult::CANNOT_DELETE_SELF;

    Account* friendAccount = storage.findAccountByID(ID);

    if(!friendAccount) return DeleteFriendResult::INVALID_ID;
    if(!currentAccount -> isHeMyFriend(ID)) return DeleteFriendResult::NOT_FRIEND;

    currentAccount -> deleteFriend(ID);
    friendAccount -> deleteFriend(currentAccount -> getID());
    return DeleteFriendResult::SUCCESS;
}



std::vector<Project*> Session::getCurrentUserProjects() const {
    assert(currentAccountID != 0 && "No user logged in!");
    std::vector <Project*> result;

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);

    for(auto projectID : currentAccount -> getProjectsIDs()) {
        auto project = storage.findProjectByID(projectID);
        if (project) result.push_back(project); 
    }

    return result;
}

OpenProjectResult Session::openProject(std::uint64_t ID) {
    assert(currentAccountID != 0 && "No user logged in!");

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);    

    if(!currentAccount -> ProjectValidator(ID)) return OpenProjectResult::INVALID_ID;

    currentProjectID = ID;

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject);

    ProjectMember* member = currentProject -> findMemberByID(currentAccount -> getID());
    if(!member) return OpenProjectResult::INVALID_ID;
    
    switch(member -> getRole()) {
        case Role::USER : return OpenProjectResult::USER;
        case Role::ADMIN : return OpenProjectResult::ADMIN;
        case Role::OWNER : return OpenProjectResult::OWNER;
    }
}

void Session::addProject(const std::string &name) {
    assert(currentAccountID != 0 && "No user logged in!");

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);

    std::uint64_t projectID = storage.addProject(name, currentAccount -> getID(), Role::OWNER);
    currentAccount -> addProjectID (projectID);
}

DeleteProjectResult Session::deleteProject(std::uint64_t ID) {
    assert(currentAccountID != 0 && "No user logged in!");

    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);

    Project* project = storage.findProjectByID(ID);
    if (!project) return DeleteProjectResult::INVALID_ID;

    ProjectMember* currentMember = project -> findMemberByID (currentAccount -> getID());
    if (!currentMember) return DeleteProjectResult::INVALID_ID;

    if(currentMember -> getRole() != Role::OWNER) return DeleteProjectResult::NO_PERMISSION;

    storage.deleteProject(ID);
    return DeleteProjectResult::SUCCESS;
}



std::vector <Task> Session::getCurrentProjectTasks() const{
    assert(currentProjectID != 0 && "No project opened!");
    std::vector <Task> result;

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject);

    for(const auto& task : currentProject -> getTasks()) {
        result.push_back(task);
    }

    return result;
}

OpenTaskResult Session::openTask(std::uint64_t ID) {
    assert(currentProjectID != 0 && "No project opened!");

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject);

    if(!currentProject -> taskValidator(ID)) return OpenTaskResult::INVALID_ID;

    currentTaskID = ID;
    return OpenTaskResult::SUCCESS;
}

void Session::addTask(const std::string &name){
    assert(currentProjectID != 0 && "No project opened!");

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject);

    currentProject -> addTask(name);
}
bool Session::deleteTask(std::uint64_t ID) {
    assert(currentProjectID != 0 && "No project opened!");

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject);

    return currentProject -> deleteTask(ID);
}
void Session::changeTaskStatus(){
    assert(currentProjectID != 0 && "No project opened!");

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject);

    Task* currentTask = currentProject -> findTaskByID(currentTaskID);
    assert(currentTask);

    currentTask -> changeStatus();
}
bool Session::getIsDone() const{
     assert(currentProjectID != 0 && "No project opened!");

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject);

    Task* currentTask = currentProject -> findTaskByID(currentTaskID);
    assert(currentTask);

    return currentTask -> getIsDone();
}


bool Session::alreadyInProject(std::uint64_t ID) const{ // do projektu to dodaj
    assert(currentProjectID != 0 && "No project opened!");

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject != nullptr);
    
    for (const auto& member : currentProject -> getProjectMembers()){
        if (ID == member.getID()) {
            return true;
        }
    }
    return false;
}



std::vector <Account*> Session::getAvailableMembersAccounts() const {
    assert(currentAccountID != 0 && "User not logged in!");

    std::vector <Account*> result;
    
    Account* currentAccount = storage.findAccountByID(currentAccountID);
    assert(currentAccount);

    for(auto friendID : currentAccount -> getFriendsIDs()) {
        if(!alreadyInProject(friendID)) {
            Account* acc = storage.findAccountByID(friendID);
            if(acc) result.push_back(acc);
        }
    }

    return result;
}

std::vector <MemberView> Session::getProjectMembersView() const{
    assert(currentProjectID != 0 && "No project opened!");

    std::vector <MemberView> result;

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject);

    for(const auto& member : currentProject -> getProjectMembers()) {
        auto acc = storage.findAccountByID(member.getID());
        assert(acc != nullptr && "Member account should exist!");

        result.push_back({
            member.getID(), 
            acc -> getUsername(), 
            member.roleToString()
        });
    }

    return result;
}

AddMemberResult Session::addMember(std::uint64_t ID, Role role) {
    assert(currentProjectID != 0 && "No project opened!");

    if(alreadyInProject(ID)) return AddMemberResult::ALREADY_IN_PROJECT;

    auto member = storage.findAccountByID(ID);
    if(!member) return AddMemberResult::INVALID_ID;

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject);
    currentProject -> addMember(ID, role);
    member -> addProjectID(currentProjectID);

    return AddMemberResult::SUCCESS;
}

DeleteMemberResult Session::deleteMember(std::uint64_t ID) {
    assert(currentProjectID != 0 && "No project opened!");

    if(currentAccountID == ID) return DeleteMemberResult::CANNOT_DELETE_SELF;

    auto member = storage.findAccountByID(ID);
    if(!member) return DeleteMemberResult::INVALID_ID;

    if(!alreadyInProject(ID)) return DeleteMemberResult::IS_NOT_MEMBER;

    Project* currentProject = storage.findProjectByID(currentProjectID);
    assert(currentProject);

    currentProject -> deleteMember(ID);
    member -> deleteProjectID(currentProjectID);
    return DeleteMemberResult::SUCCESS;

}



bool Session::isLogged() const{
    return currentAccountID != 0;
}



void Session::logout() {
    currentAccountID = 0;
    currentProjectID = 0;
    currentTaskID = 0;
}
void Session::exitProject() {
    currentProjectID = 0;
}
void Session::exitTask() {
    currentTaskID = 0;
}
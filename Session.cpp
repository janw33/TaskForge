#include "Session.h"

Session::Session(Storage &storage)
    :storage(storage), currentAccount(nullptr), currentProject(nullptr), currentTask(nullptr)
{
}



RegisterResult Session::signUp(const std::string &username, const std::string &password) {
    if(storage.isUsernameTaken(username)) return RegisterResult::USERNAME_TAKEN;

    auto newAccount = storage.addAccount(username, password);

    currentAccount = newAccount;
    return RegisterResult::SUCCESS;
}

LoginResult Session::login(const std::string &username, const std::string &password) {
    auto acc = storage.findAccountByUsername(username);

    if(!acc) return LoginResult::INVALID_USERNAME;
    if(acc -> getPassword() != password) return LoginResult::INVALID_PASSWORD;

    currentAccount = acc;
    return LoginResult::SUCCESS;
}



ChangeUsernameResult Session::changeUsername(const std::string &newUsername) {
    assert(currentAccount && "No user logged in!");

    if(currentAccount -> getUsername() == newUsername) return ChangeUsernameResult::SAME_AS_OLD;
    if(storage.isUsernameTaken(newUsername)) return ChangeUsernameResult::USERNAME_TAKEN;

    currentAccount->setUsername(newUsername);
    return ChangeUsernameResult::SUCCESS;
}

ChangePasswordResult Session::changePassword(const std::string &newPassword) {
    assert(currentAccount && "No user logged in!");
    if(currentAccount -> getPassword() == newPassword) return ChangePasswordResult::SAME_AS_OLD;

    currentAccount->setPassword(newPassword);
    return ChangePasswordResult::SUCCESS;
}

DeleteAccountResult Session::deleteAccount() {
    assert(currentAccount && "No user logged in!");
    auto projects = currentAccount->getProjectsIDs();

    for(auto projectID : projects) {
        Project* prj = storage.findProjectByID(projectID);
        if(!prj) continue;

        ProjectMember* member = prj -> findMemberByID(currentAccount -> getID());
        if(!member) continue;

        if(member -> getRole() == Role::OWNER) storage.deleteProject(projectID);
            else prj -> deleteMember(currentAccount -> getID());
    }

    storage.deleteAccount(currentAccount -> getID());
    logout();
    return DeleteAccountResult::SUCCESS;
}



std::vector<Account> Session::getAvailableAccounts() const {
    assert(currentAccount && "No user logged in!");
    std::vector <Account> result;

    const auto& friends = currentAccount->getFriendsIDs();

    for (const auto& account : storage.getAccounts()) {

        if (account.getID() == currentAccount->getID()) continue;

        bool isFriend = false;

        for (auto friendID : friends) {
            if (friendID == account.getID()) {
                isFriend = true;
                break;
            }
        }

        if (!isFriend) result.push_back(account);
    }
    return result;
}

std::vector<Account*> Session::getCurrentUserFriends() const {
    assert(currentAccount && "No user logged in!");
    std::vector <Account*> result;

    for(auto friendID : currentAccount -> getFriendsIDs()) {
        auto f = storage.findAccountByID(friendID);
        if (f) result.push_back(f); 
    }

    return result;
}

AddFriendResult Session::addFriend(std::uint64_t ID) {
    assert(currentAccount && "No user logged in!");
    if(ID == currentAccount -> getID()) return AddFriendResult::CANNOT_ADD_SELF;

    Account* friendAccount = storage.findAccountByID(ID);

    if(!friendAccount) return AddFriendResult::INVALID_ID;
    if(currentAccount -> isHeMyFriend(ID)) return AddFriendResult::ALREADY_YOUR_FRIEND;

    currentAccount -> addFriend(ID);
    friendAccount -> addFriend(currentAccount -> getID());
    return AddFriendResult::SUCCESS;
}

DeleteFriendResult Session::deleteFriend(std::uint64_t ID) {
    assert(currentAccount && "No user logged in!");
    if(ID == currentAccount -> getID()) return DeleteFriendResult::CANNOT_DELETE_SELF;

    Account* friendAccount = storage.findAccountByID(ID);

    if(!friendAccount) return DeleteFriendResult::INVALID_ID;
    if(!currentAccount -> isHeMyFriend(ID)) return DeleteFriendResult::NOT_FRIEND;

    currentAccount -> deleteFriend(ID);
    friendAccount -> deleteFriend(currentAccount -> getID());
    return DeleteFriendResult::SUCCESS;
}



std::vector<Project*> Session::getCurrentUserProjects() const {
    assert(currentAccount && "No user logged in!");
    std::vector <Project*> result;

    for(auto projectID : currentAccount -> getProjectsIDs()) {
        auto project = storage.findProjectByID(projectID);
        if (project) result.push_back(project); 
    }

    return result;
}

OpenProjectResult Session::openProject(std::uint64_t ID) {
    assert(currentAccount && "No user logged in!");

    Project* prj = storage.findProjectByID(ID);
    if(!prj) return OpenProjectResult::INVALID_ID;

    currentProject = prj;

    ProjectMember* member = currentProject -> findMemberByID(currentAccount -> getID());
    if(!member) return OpenProjectResult::INVALID_ID;
    
    switch(member -> getRole()) {
        case Role::USER : return OpenProjectResult::USER;
        case Role::ADMIN : return OpenProjectResult::ADMIN;
        case Role::OWNER : return OpenProjectResult::OWNER;
    }
}

void Session::addProject(const std::string &name) {
    assert(currentAccount && "No user logged in!");
    std::uint64_t projectID = storage.addProject(name, currentAccount -> getID(), Role::OWNER);
    currentAccount -> addProjectID (projectID);
}

DeleteProjectResult Session::deleteProject(std::uint64_t ID) {
    assert(currentAccount && "No user logged in!");

    Project* project = storage.findProjectByID(ID);
    if (!project) return DeleteProjectResult::INVALID_ID;

    ProjectMember* currentMember = project -> findMemberByID (currentAccount -> getID());
    if (!currentMember) return DeleteProjectResult::INVALID_ID;

    if(currentMember -> getRole() != Role::OWNER) return DeleteProjectResult::NO_PERMISSION;

    storage.deleteProject(ID);
    return DeleteProjectResult::SUCCESS;
}



std::vector <Task> Session::getCurrentProjectTasks() const{
    assert(currentProject && "No project opened!");
    std::vector <Task> result;
    for(const auto& task : currentProject -> getTasks()) {
        result.push_back(task);
    }

    return result;
}

OpenTaskResult Session::openTask(std::uint64_t ID) {
    assert(currentProject && "No project opened!");
    Task* tsk = currentProject -> findTaskByID(ID);

    if(!tsk) return OpenTaskResult::INVALID_ID;

    currentTask = tsk;
    return OpenTaskResult::SUCCESS;
}

void Session::addTask(const std::string &name){
    assert(currentProject && "No project opened!");
    currentProject -> addTask(name);
}
bool Session::deleteTask(std::uint64_t ID) {
    assert(currentProject && "No project opened!");
    if(currentProject -> deleteTask(ID)) return true;
    else return false;
}
void Session::changeTaskStatus(){
    currentTask -> changeStatus();
}
bool Session::getIsDone() const{
    return currentTask -> getIsDone();
}


bool Session::alreadyInProject(std::uint64_t ID) const{
    assert(currentProject && "No project opened!");
    for (const auto& member : currentProject -> getProjectMembers()){
        if (ID == member.getID()) {
            return true;
        }
    }
    return false;
}



std::vector <Account*> Session::getAvailableMembersAccounts() const {
    assert(currentProject && "No project opened!");

    std::vector <Account*> result;

    for(auto friendID : currentAccount -> getFriendsIDs()) {
        if(!alreadyInProject(friendID)) {
            Account* acc = storage.findAccountByID(friendID);
            if(acc) result.push_back(acc);
        }
    }

    return result;
}

std::vector <MemberView> Session::getProjectMembersView() const{
    assert(currentProject && "No project opened!");

    std::vector <MemberView> result;
    for(const auto& member : currentProject -> getProjectMembers()) {
        auto acc = storage.findAccountByID(member.getID());
        result.push_back({
            member.getID(), 
            acc -> getUsername(), 
            member.roleToString()
        });
    }

    return result;
}

AddMemberResult Session::addMember(std::uint64_t ID, Role role) {
    assert(currentProject && "No project opened!");

    if(alreadyInProject(ID)) return AddMemberResult::ALREADY_IN_PROJECT;

    auto member = storage.findAccountByID(ID);
    if(!member) return AddMemberResult::INVALID_ID;

    currentProject -> addMember(ID, role);
    member -> addProjectID(currentProject -> getID());

    return AddMemberResult::SUCCESS;
}

DeleteMemberResult Session::deleteMember(std::uint64_t ID) {
    assert(currentProject && "No project opened!");

    if(currentAccount -> getID() == ID) return DeleteMemberResult::CANNOT_DELETE_SELF;

    auto member = storage.findAccountByID(ID);
    if(!member) return DeleteMemberResult::INVALID_ID;

    if(!alreadyInProject(ID)) return DeleteMemberResult::IS_NOT_MEMBER;

    currentProject -> deleteMember(ID);
    member -> deleteProjectID(currentProject -> getID());
    return DeleteMemberResult::SUCCESS;

}



bool Session::isLogged() {
    return currentAccount != nullptr;
}



void Session::logout() {
    currentAccount = nullptr;
    currentProject = nullptr;
    currentTask = nullptr;
}
void Session::exitProject() {
    currentProject = nullptr;
}
void Session::exitTask() {
    currentTask = nullptr;
}
#include "Session.h"

Session::Session(Storage &storage)
    :storage(storage), currentAccount(nullptr), currentProject(nullptr), currentTask(nullptr)
{
}



RegisterResult Session::signUp(const std::string &username, const std::string &password) {
    if(storage.isUsernameTaken(username)) return RegisterResult::USERNAME_TAKEN;

    auto newAccount = storage.addAccount(username, password);

    setCurrentAccount(newAccount);
    return RegisterResult::SUCCESS;
}

LoginResult Session::login(const std::string &username, const std::string &password) {
    auto acc = storage.findAccountByUsername(username);

    if(!acc) return LoginResult::INVALID_USERNAME;
    if(acc -> getPassword() != password) return LoginResult::INVALID_PASSWORD;

    setCurrentAccount(acc);
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

    setCurrentProject(prj);

    ProjectMember* member = findMemberByID(currentAccount -> getID());
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



const Account* Session::getCurrentAccount() const{
    if(currentAccount) return currentAccount;
    else return nullptr;
}
const Project* Session::getCurrentProject() const{
    if(currentProject) return currentProject;
    else return nullptr;
}
const Task* Session::getCurrentTask() const{
    if(currentTask) return currentTask;
    else return nullptr;
}






ProjectMember* Session::findMemberByID(std::uint64_t ID) {
    return currentProject -> findMemberByID(ID);
}
void Session::addMember(std::uint64_t ID, Role role) {
    currentProject -> addMember(ID, role);
}
bool Session::deleteMember(std::uint64_t ID) {
    return currentProject -> deleteMember(ID);
}

Task* Session::findTaskByID(std::uint64_t ID){
    return currentProject -> findTaskByID(ID);
}



void Session::addTask(const std::string &name){
    currentProject -> addTask(name);
}



bool Session::deleteTask(std::uint64_t ID) {
    if(currentProject -> deleteTask(ID)) return true;
        else return false;
}

void Session::changeTaskStatus(){
    currentTask -> changeStatus();
}
bool Session::getIsDone() const{
    return currentTask -> getIsDone();
}



void Session::setCurrentAccount(Account* acc) {
    currentAccount = acc;
}
void Session::setCurrentProject(Project* prj) {
    currentProject = prj;
}
void Session::setCurrentTask(Task* tsk){
    currentTask = tsk;
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
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

void Session::changeUsername(const std::string &newUsername) {
    currentAccount->setUsername(newUsername);
}
void Session::changePassword(const std::string &newPassword) {
    currentAccount->setPassword(newPassword);
}

Account* Session::getCurrentAccount() {
    if(currentAccount) return currentAccount;
    else return nullptr;
}
Project* Session::getCurrentProject() {
    if(currentProject) return currentProject;
    else return nullptr;
}
Task* Session::getCurrentTask() {
    if(currentTask) return currentTask;
    else return nullptr;
}



void Session::addProjectID(std::uint64_t ID) {
    currentAccount -> addProjectID(ID);
}


bool Session::deleteProjectID(std::uint64_t ID) {
    if(currentAccount -> deleteProjectID(ID)) return true;
    else return false;
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
bool Session::isHeMyFriend(std::uint64_t ID){
    return currentAccount -> isHeMyFriend(ID);
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
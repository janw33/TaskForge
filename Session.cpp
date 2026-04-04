#include "Session.h"

Session::Session()
    :currentAccount(nullptr), currentProject(nullptr)
{
}



bool Session::isAccountOpened() {
    return currentAccount;
}
bool Session::isProjectOpened() {
    return currentProject;
}
bool Session::isTaskOpened() {
    return currentTask;
}



void Session::changeUsername(const std::string &newUsername) {
    currentAccount->setUsername(newUsername);
}
void Session::changePassword(const std::string &newPassword) {
    currentAccount->setPassword(newPassword);
}



std::uint64_t Session::getAccountID() const {
    return currentAccount -> getID();
}
const std::vector<Project> &Session::getProjects() const {
    return currentAccount -> getProjects();
}
const std::vector<Task> &Session::getTasks() const{
    return currentProject -> getTasks();
}
const std::vector<std::uint64_t> &Session::getFriendsIDs() const {
    return currentAccount -> getFriendsIDs();
}


Project* Session::findProjectByID (std::uint64_t ID) {
    return currentAccount -> findProjectByID(ID);
}




void Session::addProject(const std::string &name) {
    currentAccount -> addProject(name);
}

std::ptrdiff_t Session::findProjectIndexByID(std::uint64_t ID) {
    return currentAccount -> findProjectIndexByID(ID);
}
bool Session::deleteProject(std::uint64_t ID) {
    std::ptrdiff_t index = findProjectIndexByID(ID);
    if(index == -1) return false;

    currentAccount -> deleteProject(index);
    return true;
}



Task* Session::findTaskByID(std::uint64_t ID){
    return currentProject -> findTaskByID(ID);
}



void Session::addTask(const std::string &name){
    currentProject -> addTask(name);
}

std::ptrdiff_t Session::findTaskIndexByID(std::uint64_t ID){
    return currentProject -> findTaskIndexByID(ID);
}
bool Session::deleteTask(std::uint64_t ID) {
    std::ptrdiff_t index = findTaskIndexByID(ID);
    if(index == -1) return false;

    currentProject -> deleteTask(index);
    return true;
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
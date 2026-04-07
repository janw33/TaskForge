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
const std::string &Session::getAccountUsername() const {
    return currentAccount -> getUsername();
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
const std::vector<ProjectMember> &Session::getProjectMembers() const {
    return currentProject -> getProjectMembers();
}



Project* Session::findProjectByID (std::uint64_t ID) {
    return currentAccount -> findProjectByID(ID);
}




void Session::addProject(const std::string &name) {
    currentAccount -> addProject(name, getAccountID(), getAccountUsername());
}


bool Session::deleteProject(std::uint64_t ID) {
    if(currentAccount -> deleteProject(ID)) return true;
        else return false;
}


ProjectMember* Session::findMemberByID(std::uint64_t ID) {
    return currentProject -> findMemberByID(ID);
}
void Session::addMember(std::uint64_t ID,const std::string& username, Role role) {
    currentProject -> addMember(ID, username, role);
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
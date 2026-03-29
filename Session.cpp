#include "Session.h"

Session::Session()
    :currentAccount(nullptr), currentProject(nullptr)
{
}

void Session::changeUsername(const std::string &newUsername) {
    if (currentAccount) {
    currentAccount->setUsername(newUsername);
    }
}
void Session::changePassword(const std::string &newPassword) {
    if (currentAccount) {
    currentAccount->setPassword(newPassword);
    }
}

const std::string &Session::getUsername() const{
    return currentAccount -> getUsername();
}
const std::vector<Project> &Session::getProjects() const {
    return currentAccount -> getProjects();
}

Project* Session::findProjectByID (std::uint64_t ID) {
    return currentAccount -> findProjectByID(ID);
}
std::ptrdiff_t Session::findProjectIndexByID(std::uint64_t ID) {
    return currentAccount -> findProjectIndexByID(ID);
}

void Session::addProject(const std::string &name) {
    currentAccount -> addProject(name);
}
void Session::deleteProject(size_t index) {
    currentAccount -> deleteProject(index);
}

void Session::setCurrentAccount(Account* acc) {
    currentAccount = acc;
}
void Session::setCurrentProject(Project* prj) {
    currentProject = prj;
}
void Session::logout()
{
    currentAccount = nullptr;
    currentProject = nullptr;
}
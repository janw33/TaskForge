#include "Storage.h"

Storage::Storage()
    :nextAccountID(1), nextProjectID(1)
{
}


Account* Storage::findAccountByID(std::uint64_t ID) {
    auto it = accounts.find(ID);
    if(it != accounts.end()) return &it -> second;

    return nullptr;
}



bool Storage::isUsernameTaken(const std::string &username) {
    auto it = accountUsernameToID.find(username);
    if(it != accountUsernameToID.end()) return true;

    return false;
}
std::uint64_t Storage::addAccount(const std::string &username, const std::string &password) {
    std::uint64_t accountID = nextAccountID++;

    accounts.emplace(accountID, Account(username, password, accountID));
    accountUsernameToID.emplace(username, accountID);

    return accountID;
}

std::uint64_t Storage::findAccountIDByUsername(const std::string &username) {
    auto it = accountUsernameToID.find(username);
    if(it != accountUsernameToID.end()) return it -> second;

    return 0;
}



void Storage::deleteAccount(std::uint64_t ID, const std::string &username) {
    auto acc = findAccountByID(ID);
    if(!acc) return;

    auto projects = acc->getProjectsIDs();

    for(auto project : projects) {
        deleteProject(project);
    }

    accounts.erase(ID);
    accountUsernameToID.erase(username);
}

Project* Storage::findProjectByID(std::uint64_t ID){
    auto it = projects.find(ID);
    if(it != projects.end()) return &it -> second;

    return nullptr;
}
std::uint64_t Storage::addProject(const std::string &name, std::uint64_t userID, Role role) {
    std::uint64_t nextID = nextProjectID++;
    projects.emplace(nextID, Project(name, nextID, userID, role));

    return nextID;
}



void Storage::deleteProject(std::uint64_t ID) {
    Project* prj = findProjectByID(ID);
    if (!prj) return;

    for (const auto& member : prj->getProjectMembers()) {
        Account* acc = findAccountByID(member.getID());
        if (acc) acc->deleteProjectID(ID);
    }

    projects.erase(ID);
}



const std::unordered_map<uint64_t, Account> &Storage::getAccounts() const {
    return accounts;
}
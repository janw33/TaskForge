#include "AccountManager.h"

AccountManager::AccountManager()
    : nextId(1), currentAccountId(-1)
{
}

int AccountManager::findAccountIndexById(int id) {
    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].getId() == id) {
            return i;
        }
    }
    return -1; 
}

bool AccountManager::isUsernameTaken(const std::string &username)
{
    for (const auto& acc : accounts)
    {
        if (acc.getUsername() == username)
        {
            return true;
        }
    }
    return false;
}

void AccountManager::addAccount(const std::string &username, const std::string &password)
{ 
        accounts.emplace_back(username, password, nextId);
        currentAccountId = nextId;
        nextId++;
}



bool AccountManager::login(const std::string& username, const std::string& password)
{
    for (const auto& acc : accounts)
    {
        if (acc.getUsername() == username && acc.getPassword() == password)
        {
            currentAccountId = acc.getId();
            return true;
        }
    }
    return false;
}


void AccountManager::changeUsername(const std::string &newUsername)
{
    int index = findAccountIndexById(currentAccountId);
    if (index == -1) return;
    auto &acc = accounts[index]; 
    acc.setUsername(newUsername);
}

void AccountManager::changePassword(const std::string &newPassword)
{
    int index = findAccountIndexById(currentAccountId);
    if (index == -1) return;
    auto &acc = accounts[index];
    acc.setPassword(newPassword);
}

void AccountManager::deleteAccount()
{
    int index = findAccountIndexById(currentAccountId);
    if (index == -1) return;
    accounts.erase(accounts.begin() + index);
    logout();
}

void AccountManager::logout(){
    currentAccountId = -1;
}
#include "AccountManager.h"

AccountManager::AccountManager()
    : nextId(1), currentAccount(nullptr)
{
}

bool AccountManager::isUsernameTaken(const std::string &username) const
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
        accounts.emplace_back(username, password, nextId++);
        currentAccount = &accounts.back();
}



bool AccountManager::login(const std::string& username, const std::string& password)
{
    for(size_t i = 0; i<accounts.size(); i++)
    {
        const auto& acc = accounts[i];

        if(acc.getUsername() == username && acc.getPassword() == password)
        {
            currentAccount = &accounts[i];
            return true;
        }
    }
    currentAccount = nullptr;
    return false;
}


void AccountManager::changeUsername(const std::string &newUsername)
{
    if (currentAccount) {
    currentAccount->setUsername(newUsername);
    }
}

void AccountManager::changePassword(const std::string &newPassword)
{
    if (currentAccount) {
    currentAccount->setPassword(newPassword);
    }
}

void AccountManager::deleteAccount()
{
    if(!currentAccount) return;

    for(size_t i = 0; i<accounts.size(); i++)
    {
        if(&accounts[i] == currentAccount)
        {
            accounts.erase(accounts.begin() + i);
            break;
        }
    }

    currentAccount = nullptr;
}

int AccountManager::findCurrentProjectIndexById(int id) const
{
    return currentAccount -> findProjectIndexById(id);
}

void AccountManager::addProjectToCurrent(const std::string &name)
{
    currentAccount -> addProject(name);
}
void AccountManager::deleteCurrentProject(size_t index)
{
    currentAccount -> deleteProject(index);
}
const std::vector<Project>& AccountManager::getCurrentProjects() const
{
    return currentAccount -> getProjects();
}
void AccountManager::logout()
{
    currentAccount = nullptr;
}
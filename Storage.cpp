#include "Storage.h"

Storage::Storage()
    :nextID(1)
{
}
Account* Storage::findAccountByUsername(const std::string &username) {
    for(size_t i = 0; i < accounts.size(); i++) 
    {
        const auto& acc = accounts[i];

        if(acc.getUsername() == username) return &accounts[i];
    }
    return nullptr;
}
std::ptrdiff_t Storage::findAccountIndexByUsername(const std::string &username) {
    for(size_t i = 0; i < accounts.size(); i++) 
    {
        const auto& acc = accounts[i];

        if(acc.getUsername() == username) return i;
    }
    return -1;
}
bool Storage::isUsernameTaken(const std::string &username)
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
bool Storage::validateCredentials(const std::string &username, const std::string &password)
{
    for(const auto& acc : accounts)
    {
        if(acc.getUsername() == username && acc.getPassword() == password)
        {
            return true;
        }
    }
    
    return false;
}

void Storage::addAccount(const std::string &username,const std::string& password)
{
    accounts.emplace_back(username, password, nextID++);
}
void Storage::deleteAccount(size_t index)
{
    accounts.erase(accounts.begin() + index);
}
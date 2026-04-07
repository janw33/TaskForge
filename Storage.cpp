#include "Storage.h"

Storage::Storage()
    :nextID(1)
{
}


Account* Storage::findAccountByID(std::uint64_t ID) {
    for(size_t i = 0; i < accounts.size(); i++) 
        if(accounts[i].getID() == ID) return &accounts[i];

    return nullptr;
}



bool Storage::isUsernameTaken(const std::string &username) {
    for (const auto& acc : accounts)
        if (acc.getUsername() == username) return true;

    return false;
}
Account* Storage::logIn(const std::string &username, const std::string &password) {
    for(size_t i = 0; i < accounts.size(); i++) {
        if(accounts[i].getUsername() == username && accounts[i].getPassword() == password) return &accounts[i];
    }

    return nullptr;
}



Account* Storage::signUp(const std::string &username,const std::string& password) {
    accounts.emplace_back(username, password, nextID++);
    return &accounts.back();
}



std::ptrdiff_t Storage::findAccountIndexByID(std::uint64_t ID) {
    for(size_t i = 0; i < accounts.size(); i++) 
        if(accounts[i].getID() == ID) return i;

    return -1;
}
bool Storage::deleteAccount(std::uint64_t ID) {
    std::ptrdiff_t index = findAccountIndexByID(ID);
    if(index == -1) return false;

    accounts.erase(accounts.begin() + index);
    return true;
}



bool Storage::addFriend(std::uint64_t ID, std::uint64_t ID2){
    Account* a = findAccountByID(ID);
    Account* b = findAccountByID(ID2);

    if(!a || !b) return false;
    if(ID == ID2) return false;

    a -> addFriend(ID2);
    b -> addFriend(ID);
    return true;
}
bool Storage::deleteFriend(std::uint64_t ID, std::uint64_t ID2){
    Account* a = findAccountByID(ID);
    Account* b = findAccountByID(ID2);

    if(!a || !b) return false;
    if(ID == ID2) return false;

    if(!a -> deleteFriend(ID2)) return false;
    if(!b -> deleteFriend(ID)) return false;

    return true;
}

const std::vector<Account> &Storage::getAccounts() const {
    return accounts;
}
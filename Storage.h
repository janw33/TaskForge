#pragma once
#include "Account.h"

class Storage
{  
    private:
    std::vector<Account>accounts;
    std::uint64_t nextID;

    public:
    Storage();
    Account* findAccountByUsername(const std::string &username); 
    std::ptrdiff_t findAccountIndexByUsername(const std::string &username);
    
    bool isUsernameTaken(const std::string &username);
    bool validateCredentials(const std::string &usenrame, const std::string &password);

    void addAccount(const std::string &username,const std::string &password);
    void deleteAccount(size_t index);
};
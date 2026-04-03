#pragma once
#include "Account.h"

class Storage
{  
    private:
    std::vector<Account>accounts;
    std::uint64_t nextID;

    std::ptrdiff_t findAccountIndexByID(std::uint64_t ID);

    public:
    Storage();

    Account* findAccountByUsername(const std::string &username); 
    
    bool isUsernameTaken(const std::string &username);
    bool validateCredentials(const std::string &usenrame, const std::string &password);

    void addAccount(const std::string &username,const std::string &password);
    bool deleteAccount(std::uint64_t ID);
};
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

    Account* findAccountByID(std::uint64_t ID);
    Account* findAccountByUsername(const std::string &username); 
    
    bool isUsernameTaken(const std::string &username);
    bool validateCredentials(const std::string &usenrame, const std::string &password);

    void addAccount(const std::string &username,const std::string &password);
    bool deleteAccount(std::uint64_t ID);

    bool addFriend(std::uint64_t ID, std::uint64_t ID2);
    bool deleteFriend(std::uint64_t ID, std::uint64_t ID2);
    const std::vector<Account> &getAccounts() const;
};
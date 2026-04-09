#pragma once
#include "Account.h"


class Storage
{  
    private:
    std::vector<Account>accounts;
    std::uint64_t nextAccountID;
    std::vector<Project>projects;
    std::uint64_t nextProjectID;

    std::ptrdiff_t findAccountIndexByID(std::uint64_t ID);
    std::ptrdiff_t findProjectIndexByID(std::uint64_t ID);
    public:
    Storage();

    Account* findAccountByID(std::uint64_t ID);
    
    bool isUsernameTaken(const std::string &username);
    Account* logIn(const std::string &usenrame, const std::string &password);

    Account* signUp(const std::string &username,const std::string &password);
    bool deleteAccount(std::uint64_t ID);

    bool addFriend(std::uint64_t ID, std::uint64_t ID2);
    bool deleteFriend(std::uint64_t ID, std::uint64_t ID2);

    Project* findProjectByID(std::uint64_t ID);
    std::uint64_t addProject(const std::string &name, std::uint64_t userID, Role role);
    bool deleteProject(std::uint64_t ID);

    const std::vector<Account> &getAccounts() const;
};
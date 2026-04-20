#pragma once
#include <unordered_map>
#include "Account.h"


class Storage
{  
    private:
    std::unordered_map <std::uint64_t, Account> accounts;
    std::unordered_map <std::string, std::uint64_t> accountUsernameToID;
    std::unordered_map <std::uint64_t, Project>projects;


    std::uint64_t nextAccountID;
    std::uint64_t nextProjectID;
    public:
    Storage();

    Account* findAccountByID(std::uint64_t ID) ;
    std::uint64_t findAccountIDByUsername(const std::string &username);

    bool isUsernameTaken(const std::string &username);

    std::uint64_t addAccount(const std::string &username, const std::string &password);
    void deleteAccount(std::uint64_t ID, const std::string &username);

    Project* findProjectByID(std::uint64_t ID);
    
    std::uint64_t addProject(const std::string &name, std::uint64_t userID, Role role);
    void deleteProject(std::uint64_t ID);

    const std::unordered_map<uint64_t, Account> &getAccounts() const;
};
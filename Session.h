#pragma once
#include "Storage.h"

enum class RegisterResult {
    SUCCESS,
    USERNAME_TAKEN
};


enum class LoginResult {
    SUCCESS,
    INVALID_USERNAME,
    INVALID_PASSWORD
};

class Session
{
    private:
    Storage &storage;
    Account* currentAccount;
    Project* currentProject;
    Task* currentTask;

    public:
    Session(Storage &storage);

    RegisterResult signUp(const std::string &username,const std::string &password);
    LoginResult login(const std::string &username, const std::string &password);

    void changeUsername(const std::string& newUsername);
    void changePassword(const std::string& newPassword);

    Account *getCurrentAccount();
    Project *getCurrentProject();
    Task* getCurrentTask();


    void addProjectID(std::uint64_t ID);
    bool deleteProjectID(std::uint64_t ID);

    ProjectMember* findMemberByID(std::uint64_t ID);
    void addMember(std::uint64_t ID, Role role);
    bool deleteMember(std::uint64_t ID);

    Task* findTaskByID(std::uint64_t ID);

    void addTask(const std::string &name);
    bool deleteTask(std::uint64_t ID);
    void changeTaskStatus();
    bool getIsDone() const;

    void setCurrentAccount(Account* acc);
    void setCurrentProject(Project* prj);
    void setCurrentTask(Task* tsk);

    bool isHeMyFriend(std::uint64_t ID);
    bool isLogged();

    void logout();
    void exitProject();
    void exitTask();
};
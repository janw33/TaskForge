#pragma once
#include "Storage.h"
#include <cassert>

enum class RegisterResult {
    SUCCESS,
    USERNAME_TAKEN
};


enum class LoginResult {
    SUCCESS,
    INVALID_USERNAME,
    INVALID_PASSWORD
};

enum class ChangeUsernameResult {
    SUCCESS,
    SAME_AS_OLD,
    USERNAME_TAKEN
};

enum class ChangePasswordResult {
    SUCCESS,
    SAME_AS_OLD
};

enum class DeleteAccountResult {
    SUCCESS
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

    ChangeUsernameResult changeUsername(const std::string& newUsername);
    ChangePasswordResult changePassword(const std::string& newPassword);
    DeleteAccountResult deleteAccount(); //dodac usuwanie projektow ktorych account byl posiadaczem

    const Account *getCurrentAccount() const;
    const Project *getCurrentProject() const;
    const Task* getCurrentTask() const;


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
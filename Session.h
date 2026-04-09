#pragma once
#include "Account.h"
#include "Project.h"
#include "Task.h"

class Session
{
    private:
    Account* currentAccount;
    Project* currentProject;
    Task* currentTask;

    public:
    Session();

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
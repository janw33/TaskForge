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

    std::ptrdiff_t findProjectIndexByID(std::uint64_t ID);
    std::ptrdiff_t findTaskIndexByID(std::uint64_t ID);
    std::ptrdiff_t findFriendIndexByID(std::uint64_t ID);
    public:
    Session();

    bool isAccountOpened();
    bool isProjectOpened();
    bool isTaskOpened();

    void changeUsername(const std::string& newUsername);
    void changePassword(const std::string& newPassword);

    std::uint64_t getAccountID() const;
    const std::vector<Project> &getProjects() const;
    const std::vector<Task> &getTasks() const;
    const std::vector<std::uint64_t> &getFriendsIDs() const;

    Project* findProjectByID(std::uint64_t ID);

    void addProject(const std::string &name);
    bool deleteProject(std::uint64_t ID);

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
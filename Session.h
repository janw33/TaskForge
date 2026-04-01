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

    const std::string &getUsername() const;
    const std::vector<Project> &getProjects() const;
    const std::vector<Task> &getTasks() const;

    Project* findProjectByID(std::uint64_t ID);
    std::ptrdiff_t findProjectIndexByID(std::uint64_t ID);

    void addProject(const std::string &name);
    void deleteProject(size_t index);

    Task* findTaskByID(std::uint64_t ID);
    std::ptrdiff_t findTaskIndexByID(std::uint64_t ID);

    void addTask(const std::string &name);
    void deleteTask(size_t index);
    void changeTaskStatus();
    bool getIsDone() const;

    void setCurrentAccount(Account* acc);
    void setCurrentProject(Project* prj);
    void setCurrentTask(Task* tsk);

    bool isLogged();
    void logout();
};
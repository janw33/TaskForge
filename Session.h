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

enum class AddFriendResult {
    SUCCESS,
    INVALID_ID,
    CANNOT_ADD_SELF,
    ALREADY_YOUR_FRIEND
};
enum class DeleteFriendResult {
    SUCCESS,
    INVALID_ID,
    NOT_FRIEND,
    CANNOT_DELETE_SELF
};

enum class OpenProjectResult {
    USER,
    ADMIN,
    OWNER,
    INVALID_ID,
};

enum class DeleteProjectResult {
    SUCCESS,
    INVALID_ID,
    NO_PERMISSION
};

enum class OpenTaskResult {
    SUCCESS,
    INVALID_ID
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

    std::vector <Account> getAvailableAccounts() const;
    std::vector <Account*> getCurrentUserFriends() const;
    AddFriendResult addFriend(std::uint64_t ID);
    DeleteFriendResult deleteFriend(std::uint64_t ID);

    std::vector <Project*> getCurrentUserProjects() const;
    OpenProjectResult openProject(std::uint64_t ID);
    void addProject(const std::string &name);
    DeleteProjectResult deleteProject(std::uint64_t ID);

    std::vector <Task> getCurrentProjectTasks() const;
    OpenTaskResult openTask(std::uint64_t ID);
    void addTask(const std::string &name);
    bool deleteTask(std::uint64_t ID);

    const Account *getCurrentAccount() const;
    const Project *getCurrentProject() const;
    const Task* getCurrentTask() const;



    ProjectMember* findMemberByID(std::uint64_t ID);
    void addMember(std::uint64_t ID, Role role);
    bool deleteMember(std::uint64_t ID);

    Task* findTaskByID(std::uint64_t ID);

    void changeTaskStatus();
    bool getIsDone() const;

    void setCurrentAccount(Account* acc);
    void setCurrentProject(Project* prj);
    void setCurrentTask(Task* tsk);

    bool isLogged();

    void logout();
    void exitProject();
    void exitTask();
};
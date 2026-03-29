#include "Account.h"
#include "Project.h"

class Session
{
    private:
    Account* currentAccount;
    Project* currentProject;

    public:
    Session();
    void changeUsername(const std::string& newUsername);
    void changePassword(const std::string& newPassword);

    const std::string &getUsername() const;
    const std::vector<Project> &getProjects() const;

    Project* findProjectByID(std::uint64_t ID);
    std::ptrdiff_t findProjectIndexByID(std::uint64_t ID);

    void addProject(const std::string &name);
    void deleteProject(size_t index);

    void setCurrentAccount(Account* acc);
    void setCurrentProject(Project* prj);

    void logout();
};
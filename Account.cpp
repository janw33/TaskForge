#include "Account.h"

Account::Account(const std::string& username, const std::string& password, int id)
	:username(username), password(password), id(id), projectNextId(1), currentProject(nullptr)
{
}



const std::string& Account::getUsername() const
{
    return username;
}

const std::string& Account::getPassword() const
{
    return password;
}

int Account::getId() const
{
    return id;
}
const std::vector<Project>& Account::getProjects() const
{
    return projects;
}


void Account::setUsername(const std::string &newUsername)
{
    username = newUsername;
}
void Account::setPassword(const std::string &newPassword)
{
    password = newPassword;
}
void Account::setCurrentProject(size_t index)
{
    currentProject = &projects[index];
}
	
int Account::findProjectIndexById(int id) const
{
    for(size_t i = 0; i < projects.size(); i++)
    {
        if(id == projects[i].getId())
        {
            return i;
        }
    }
    return -1;
}

void Account::addProject(const std::string &name)
{
    projects.emplace_back(name, projectNextId++);
}
void Account::deleteProject(size_t index)
{
    projects.erase(projects.begin() + index);
}



void Account::showCurrentTasks()
{

}
void Account::addCurrentTask(const std::string& name, int id)
{
    currentProject -> addTask(name, id);
}
void Account::deleteCurrentTask()
{

}
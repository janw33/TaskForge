#include "Project.h"

Project::Project(const std::string &name, std::uint64_t ID, std::uint64_t ownerID, const std::string &ownerUsername)
    : name(name), ID(ID), taskNextID(1)
{
    members.emplace_back(ownerID,ownerUsername, Role::OWNER);
}



const std::string & Project::getName() const
{
    return name;
}
std::uint64_t Project::getID() const
{
    return ID;
}
const std::vector<Task> &Project::getTasks() const{
    return tasks;
}
const std::vector<ProjectMember> &Project::getProjectMembers() const {
    return members;
}


void Project::addTask(const std::string& name)
{
    tasks.emplace_back(name, taskNextID++);
}
bool Project::deleteTask(std::uint64_t ID)
{
    std::ptrdiff_t index = findTaskIndexByID(ID);
    if(index == -1) return false;

    tasks.erase(tasks.begin() + index);
    return true;
}

Task* Project::findTaskByID(std::uint64_t ID){
    for(size_t i = 0; i < tasks.size(); i++)
    {
        if(ID == tasks[i].getID()) return &tasks[i];
    }
    return nullptr;
} 
std::ptrdiff_t Project::findTaskIndexByID(std::uint64_t ID){
    for(size_t i = 0; i < tasks.size(); i++)
    {
        if(ID == tasks[i].getID()) return i;
    }
    return -1;
}

ProjectMember* Project::findMemberByID(std::uint64_t ID) {
    for(size_t i = 0; i < members.size(); i++) {
        if(members[i].getID() == ID) return &members[i];
    }
    return nullptr;
}

void Project::addMember(std::uint64_t ID,const std::string &username, Role role) {
    members.emplace_back(ID,username, role);
}
std::ptrdiff_t Project::findMemberIndexByID(std::uint64_t ID){
    for(size_t i = 0; i < members.size(); i++) {
        if(members[i].getID() == ID) return i;
    }

    return -1;
}
bool Project::deleteMember(std::uint64_t ID) {
    std::ptrdiff_t index = findMemberIndexByID (ID);
    if(index == -1) return false;

    members.erase(members.begin() + index);
    return true;
}
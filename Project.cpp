#include "Project.h"

Project::Project(const std::string &name, std::uint64_t ID)
    : name(name), ID(ID), taskNextID(1)
{
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
void Project::showTasks()
{

}
void Project::addTask(const std::string& name)
{
    tasks.emplace_back(name, taskNextID++);
}
void Project::deleteTask(size_t index)
{
    tasks.erase(tasks.begin() + index);
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
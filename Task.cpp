#include "Task.h"

Task::Task(const std::string& name, const std::string& priority, int id)
    : name(name), priority(priority), id(id), isDone(false)
{
}



const std::string &Task::getName() const
{
    return name;
}

const std::string &Task::getPriority() const
{
    return priority;
}

int Task::getId() const
{
    return id;
}

bool Task::getIsDone() const
{
    return isDone;
}
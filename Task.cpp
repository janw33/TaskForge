#include "Task.h"

Task::Task(const std::string& name, int id, bool isDone)
    : name(name),  id(id), isDone(isDone)
{
}



const std::string &Task::getName() const
{
    return name;
}


int Task::getId() const
{
    return id;
}

bool Task::getIsDone() const
{
    return isDone;
}
#include "Task.h"

Task::Task(const std::string& name, std::uint64_t ID)
    : name(name),  ID(ID), isDone(false)
{
}



const std::string &Task::getName() const
{
    return name;
}


std::uint64_t Task::getID() const
{
    return ID;
}

bool Task::getIsDone() const
{
    return isDone;
}

void Task::changeStatus(){
    if(isDone == true) isDone = false;
    else isDone = true;
}

#include "Task.h"

Task::Task(const std::string& name, const std::string& priority, int id)
    : name(name), priority(priority), id(id), isDone(false)
{
}
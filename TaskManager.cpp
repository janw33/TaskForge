#include "TaskManager.h"

TaskManager::TaskManager(Interface& ui)
    : ui(ui), nextId(1)
{
}

void TaskManager::addTask()
{
    std::string name = ui.askName();
    std::string priority = ui.askPriority();
    tasks.emplace_back(name, priority, nextId++);
}
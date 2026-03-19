#include "TaskManager.h"

TaskManager::TaskManager(Interface& ui)
    : ui(ui), nextId(1)
{
}



void TaskManager::addTask()
{
    std::string name = ui.askString("Enter name: ");
    std::string priority = ui.askString("Enter priority: ");
    tasks.emplace_back(name, priority, nextId++);
}
void TaskManager::deleteTask()
{
   
}
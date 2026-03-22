#include "TaskManager.h"

TaskManager::TaskManager(Interface& ui)
    : ui(ui), taskNextId(1)
{
}



void TaskManager::addTask()
{
    std::string name = ui.askString("Enter name: ");
    std::string priority = ui.askString("Enter priority: ");
    tasks.emplace_back(name, priority, taskNextId);
    taskIdToIndex[taskNextId] = tasks.size() - 1;
    taskNextId++;
    ui.printPauseClear("Task added Successfully!");
}
void TaskManager::deleteTask()
{
    ui.print("Enter ID: ");

    for(const auto& task : tasks)
    {
        ui.print("[" + std::to_string(task.getId()) + "] " + task.getName());
    }

    std::string idStr = ui.askString("");
    int id = std::stoi(idStr);
    size_t index = taskIdToIndex[id];

    tasks.erase(tasks.begin() + index);
}
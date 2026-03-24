#include "ProjectManager.h"

ProjectManager::ProjectManager(Interface& ui)
    : ui(ui), projectNextId(1), currentProjectIndex(0)
{
}



bool ProjectManager::isIdChoiceCorrect(int id)
{
    for (size_t i = 0; i < projects.size(); i++)
    {
        const auto& projectId = projects[i].getId();

        if (id == projectId)
        {
            currentProjectIndex = i;
            return true;
        }
    }
    return false;
}

void ProjectManager::chooseProject()
{
    ui.print("Enter ID: ");

    for (const auto& project : projects)
    {
        ui.print("[" + std::to_string(project.getId()) + "] " + project.getName());
    }
    while (true)
    {
        std::string idStr = ui.askString("");
        int id = std::stoi(idStr);
        /*
        if (isIdChoiceCorrect(id))
        {
            currentProject();
        }
        else
        {
            ui.print("Invalid id");
        }
        */
    }
}


void ProjectManager::addProject()
{
    std::string name = ui.askString("Enter name: ");
    projects.emplace_back(name, projectNextId++);
    ui.printPauseClear("Project added Successfully!");
}

void ProjectManager::deleteProject()
{
    ui.print("Enter ID: ");

    for (const auto& project : projects)
    {
        ui.print("[" + std::to_string(project.getId()) + "] " + project.getName());
    }

    std::string idStr = ui.askString("");
    int id = std::stoi(idStr);

}
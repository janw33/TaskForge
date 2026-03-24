#include "Project.h"

Project::Project(const std::string &name, int id)
    : name(name), id(id), taskNextId(1)
{
}



const std::string & Project::getName() const
{
    return name;
}
int Project::getId() const
{
    return id;
}


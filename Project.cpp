#include "Project.h"

Project::Project(const std::string &name, int id)
    : name(name), id(id)
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


#pragma once
#include <algorithm>
#include "Project.h"
#include "Interface.h"

class ProjectManager
{
	Interface& ui;
	std::vector<Project> projects;
	int projectNextId;

	bool isIdChoiceCorrect(int id);
public:
	ProjectManager(Interface& ui);

	void chooseProject();
	void addProject();
	void deleteProject();
};
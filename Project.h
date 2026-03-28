#pragma once
#include <vector>


class Project
{
	std::string name;
	int id;

public:
	Project(const std::string& name, int id);

	const std::string& getName() const;
	int getId() const;
};
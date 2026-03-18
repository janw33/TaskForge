#pragma once
#include <string>

class Interface
{
public:
	void print(const std::string& message);

	void printMenu();
	int getMenuChoice(int min, int max);
	
	std::string askName();
	std::string askPriority();


	void pause();
	void clearScreen();
};
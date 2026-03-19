#pragma once
#include <string>

class Interface
{
public:
	void print(const std::string& message);
	std::string askString(const std::string& prompt);

	void printMenu();

	void printAccountMenu();
	int getChoice(int min, int max);
	
	void pause();
	void clearScreen();
};
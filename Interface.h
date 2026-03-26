#pragma once
#include <string>

class Interface
{
public:
	void print(const std::string& message);
	std::string askString(const std::string& prompt);

	void printMenu();
	void printAccountMenu();
	void printAccountSettings();
	void printProjectMenu();

	int getChoice(int min, int max);
	

	void pause();
	void clearScreen();
	void pauseClear();
	void printPauseClear(std::string error);

	std::string inputPassword(const std::string& prompt);
};
#pragma once

class Interface
{
public:
	void printMenu();
	int getMenuChoice(int min, int max);
	
	void pause();
	void clearScreen();
};
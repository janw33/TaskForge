#include "Interface.h"
#include "AccountManager.h"
#include "TaskManager.h"

int main()
{
    Interface ui;
    AccountManager accountmanager(ui);
    TaskManager taskmanager(ui);

    while (true)
    {
        bool logged = false;

        while (!logged)
        {
            ui.printMenu();
            int choice = ui.getChoice(1, 3);
            ui.clearScreen();

            switch (choice)
            {
            case 1:  accountmanager.signUp(logged); break;
            case 2:  accountmanager.logIn(logged); break;
            case 3:  ui.print("Goodbye!"); return 0;
            }
        }

        int accountChoice = 0;

        while (accountChoice != 4)
        {
            ui.printAccountMenu();
            accountChoice = ui.getChoice(1, 4);
            ui.clearScreen();

            switch (accountChoice)
            {
            case 1:break;
            case 2: taskmanager.addTask(); break;
            case 3: taskmanager.deleteTask();  break;
            case 4: ui.print("Goodbye!");  break;
            }
        }
    }
}

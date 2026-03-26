#include "Interface.h"
#include "AccountManager.h"
#include "ProjectManager.h"

int main()
{
    Interface ui;
    AccountManager accountManager(ui);
    ProjectManager projectManager(ui);

    while (true)
    {
        ui.clearScreen();
        bool logged = false;

        while (!logged)
        {
            ui.printMenu();
            int choice = ui.getChoice(1, 3);
            ui.clearScreen();

            switch (choice)
            {
            case 1:  accountManager.signUp(logged); break;
            case 2:  accountManager.logIn(logged); break;
            case 3:  ui.print("Goodbye!"); return 0;
            }
        }

        int accountChoice = 0;

        while (accountChoice != 5)
        {
            ui.printAccountMenu();
            accountChoice = ui.getChoice(1, 5);
            ui.clearScreen();

            switch (accountChoice)
            {
            case 1: projectManager.chooseProject(); break;
            case 2: projectManager.addProject(); break;
            case 3: projectManager.deleteProject();  break;
            case 4: accountManager.settings(accountChoice); break;
            case 5: ui.print("Goodbye!");  break;
            }
        }
    }
}

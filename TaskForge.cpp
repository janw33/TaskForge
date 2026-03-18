#include "Interface.h"
#include "TaskManager.h"

int main()
{
    Interface ui;
    TaskManager manager(ui);

    while (true)
    {

        ui.printMenu();
        int choice = ui.getMenuChoice(1, 4);
        ui.clearScreen();

        switch (choice)
        {
        case 1:break;
        case 2: manager.addTask();  break;
        case 3:break;
        case 4: ui.print("Goodbye!"); return 0;
        }

    }
    return 0;
}

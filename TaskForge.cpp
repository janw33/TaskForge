#include "Interface.h"

int main()
{
    Interface interface;

    while (true)
    {

        interface.printMenu();
        int choice = interface.getMenuChoice(1, 4);

        switch (choice)
        {
        case 1:break;
        case 2:break;
        case 3:break;
        case 4:break;
        }

    }
    return 0;
}

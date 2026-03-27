#include "Interface.h"
#include "AccountManager.h"

int main()
{
    AccountManager accountManager;
    Interface ui(accountManager);

    ui.run();
    
    return 0;
}

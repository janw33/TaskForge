#include "Storage.h"
#include "Session.h"
#include "Interface.h"
int main()
{
    Storage storage;
    Session session;
    Interface ui(storage, session);

    ui.run();
    
    return 0;
}

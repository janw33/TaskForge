#include "Storage.h"
#include "Session.h"
#include "Interface.h"
int main()
{
    Storage storage;
    Session session(storage);
    Interface ui(session);

    ui.run();
    
    return 0;
}

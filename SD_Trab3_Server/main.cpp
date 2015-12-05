#include <iostream>
#include "communicationmanager.h"
#include "servermanager.h"

int main(int argc, char *argv[])
{
#if 1
    if (argc != 3)
    {
        std::cout << "Invalid parameters. Correct use is: './a daemon_addr process_id'\n";
        return 1;
    }
    //
    CommunicationManager comm;
    if (comm.openConnection(argv[1], argv[2]) != ACCEPT_SESSION)
    {
        std::cout << "Server failed to connect to the Spread Daemon!\n";
        return 1;
    }
    //
    comm.joinGroup("SERVERS");
    comm.joinGroup("PROXY");
    //
    ServerManager manager(&comm);
    manager.listenRequests();
#else
    //area de teste
    ResourceManager manager;
    manager.addResource("file","location1");
    manager.addResource("file","location2");
    manager.addResource("file","location3");
    manager.printResources();
#endif

    return 0;
}

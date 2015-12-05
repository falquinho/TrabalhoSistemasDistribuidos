#include <iostream>
#include "communicationmanager.h"
#include "slavecommunicator.h"

int main(int argc, char *argv[])
{
#if 1
    if (argc != 3)
    {
        std::cout << "Invalid parameters. Correct use is: './a daemon_addr process_id'\n";
        return 1;
    }

    CommunicationManager comm;
    if (comm.openConnection(argv[1], argv[2]) != ACCEPT_SESSION)
    {
        std::cout << "Slave failed to connect to the Spread Daemon!\n";
        return 1;
    }

    comm.joinGroup("SLAVES");

    FileManager file_manager(argv[2]);
    SlaveCommunicator slave_comm(&comm, &file_manager);
    if (slave_comm.notifyProxy("register "+comm.getPrivateGroup()) < 0)
    {
        std::cout << "Failed to register @ proxy...exiting!\n";
        return 1;
    }

    slave_comm.waitOrder();

#else
    //test area
    FileManager fm;
    fm.makeFile("arq");
    fm.writeFile("arq", "conteudo");
#endif
    return 0;
}

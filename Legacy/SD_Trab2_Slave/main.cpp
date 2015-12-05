#include <iostream>
#include "slavecommunicator.h"
#include "fsemulator.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3){
        cout << "Invalid Parameters. Correct usage:\n";
        cout << "'slave port@address connection_name'\n";
        cout << "If the Daemon is local '@address' can be omited.\n";
        cout << "Default port is 4803\n";
        cout << "'connection_name' must be unique.\n";
        return 0;
    }
    //
    FSEmulator fs;
    //
    CommunicationManager manager;
    if (manager.connect(argv[1], argv[2]) != ACCEPT_SESSION)
        return 0;
    manager.join_group("SLAVES");
    //
    SlaveCommunicator comm(manager);
    comm.waitOrder(&fs);
    //
    return 0;
}


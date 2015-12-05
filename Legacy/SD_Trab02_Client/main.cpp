#include <iostream>
#include "userinterface.hpp"
#include "communicationmanager.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3){
        cout << "Invalid Parameters. Correct usage:\n";
        cout << "'client port@address connection_name'\n";
        cout << "If the Daemon is local '@address' can be omited.\n";
        cout << "Default port is 4803\n";
        cout << "'connection_name' must be unique.\n";
        return 0;
    }
    //
    CommunicationManager manager;
    int result = manager.connect(argv[1], argv[2]);
    if (result != ACCEPT_SESSION)
        return 0;
    //
    ClientCommunicator comm(manager, argv[2]);
    //
    UserInterface ux;
    ux.commandLoop(&comm);
    //
    return 0;
}

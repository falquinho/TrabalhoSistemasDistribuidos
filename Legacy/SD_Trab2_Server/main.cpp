#include <QCoreApplication>
#include "communicationmanager.h"
#include "servercommunicator.h"
#include <iostream>
#include "electionsystem.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3){
        cout << "Invalid Parameters. Correct usage:\n";
        cout << "'server port@address connection_name'\n";
        cout << "If the Daemon is local '@address' can be omited.\n";
        cout << "Default port is 4803\n";
        cout << "'connection_name' must be unique.\n";
        return 0;
    }

    //
    CommunicationManager manager;
    if (manager.connect(argv[1], argv[2]) != ACCEPT_SESSION)
        return 0;
    manager.join_group("SERVERS");
    //
    ServerCommunicator comm (manager);
    comm.listenLoop();
    //
    manager.close_connection();
    return 0;
}

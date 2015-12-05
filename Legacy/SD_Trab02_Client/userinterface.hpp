#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "clientcommunicator.h"
#include <string>
using namespace std;

class UserInterface
{
public:
    string working_dir;
    //
    UserInterface();
    int commandLoop(ClientCommunicator *comm);
    int parseCommand(string command, ClientCommunicator *comm);
    int helpScreen();
};

#endif // USERINTERFACE_H

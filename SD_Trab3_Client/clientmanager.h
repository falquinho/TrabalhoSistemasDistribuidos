#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H
#include <iostream>
#include "communicationmanager.h"
typedef std::string String;

class ClientManager
{
    CommunicationManager * communicator;
public:
    ClientManager(CommunicationManager * comm);
    void parseUserInput(String input);
    int sendGeneralRequest(String input);
    int sendMkfileRequest(String input);
    int sendRmfileRequest(String input);
    int sendWriteRequest(String input);
    String waitNotification();
    int writeFile();
};

#endif // CLIENTMANAGER_H

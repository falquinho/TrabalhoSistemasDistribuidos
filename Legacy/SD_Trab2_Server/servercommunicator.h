#ifndef SERVERCOMMUNICATOR_H
#define SERVERCOMMUNICATOR_H
#include "communicationmanager.h"
#include "electionsystem.h"

class ServerCommunicator
{
public:
    CommunicationManager manager;
    ElectionSystem elections;
    bool coordinator;
    //
    ServerCommunicator(CommunicationManager manager);
    int listenLoop();
    char *extractClient(char *mess);
    int sendOrder(char *client, short int m_type, char *mess);
};

#endif // SERVERCOMMUNICATOR_H

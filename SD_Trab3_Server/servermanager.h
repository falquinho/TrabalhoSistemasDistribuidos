#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H
#include <string>
#include "communicationmanager.h"
#include "slavesmanager.h"
#include "resourcemanager.h"
typedef std::string String;

class ServerManager
{
    SlavesManager slaves_pool;
    ResourceManager resource_manager;
    CommunicationManager *communicator;
public:
    ServerManager(CommunicationManager *comm);
    int listenRequests();
    void parseMessage(short int m_type, String sender, String mess);
    void notify(String destination, String message);
    //
    void processClientRequest(String client, String message);
    void performMakefile(String client, String filename, int copies);
    void performRemove(String client, String filename);
    void performWrite(String client, String filename);
    void performRelease(String client, String filename, String content);
    //
    void processSlaveNotification(String slave, String message);
};

#endif // SERVERMANAGER_H

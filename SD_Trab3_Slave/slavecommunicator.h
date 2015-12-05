#ifndef SLAVECOMMUNICATOR_H
#define SLAVECOMMUNICATOR_H
#include "communicationmanager.h"
#include "filemanager.h"
#include <QString>

class SlaveCommunicator
{
    CommunicationManager * communicator;
    FileManager * file_manager;
public:
    SlaveCommunicator(CommunicationManager *comm, FileManager * fm);
    int waitOrder();
    int notifyProxy(std::string mess);
    int processClientOrder(QString message);
    int processServerNotification(QString message);
    int doMkfile(QString param, QString client);
    int doRmfile(QString param, QString client);
    int doWrite(QString param, QString client);
    int writeContent(QString file, QString content);
};

#endif // SLAVECOMMUNICATOR_H

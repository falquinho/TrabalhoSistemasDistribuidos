#include "clientcommunicator.h"
#include "errorlog.h"
#include <iostream>
#include <qbytearray.h>
using namespace std;

ClientCommunicator::ClientCommunicator(CommunicationManager manager, char *client_id)
{
    this->manager = manager;
    my_id = client_id;
}

int ClientCommunicator::requestOperation(QString arg, int type, int buff_len, char *resp_buff, short int *resp_type){
    char *mess = QStringToCharArray(arg);
    int m_len = arg.size();
    //
    int result = manager.multicast(RELIABLE_MESS, "SERVERS", type, m_len, mess);
    if (result < 0)
        printError(result);
    else{
        result = waitResponse(resp_buff, buff_len, resp_type);
        if (result < 0)
            printError(result);
    }
}

int ClientCommunicator::waitResponse(char *mess, int m_size, short int *m_type){
    cout << "Waiting response...\n";
    //
    char sender[MAX_GROUP_NAME];
    service s_type = DROP_RECV;
    int no_groups;
    //
    int max_groups = 1;
    char groups[max_groups][MAX_GROUP_NAME];
    //
    int endian_mm;
    //
    int result = SP_receive(manager.mbox, &s_type, sender, max_groups, &no_groups, groups, m_type, &endian_mm, m_size, mess);
    if (result < 0)
        printError(result);
    //
    return result;
}

char *ClientCommunicator::QStringToCharArray(QString str){
    QByteArray buffer = str.toLocal8Bit();
    return buffer.data();
}

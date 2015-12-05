#ifndef CLIENTCOMMUNICATOR_H
#define CLIENTCOMMUNICATOR_H
#include "communicationmanager.h"
#include <qstring.h>


class ClientCommunicator
{
public:
    CommunicationManager manager;
    char *my_id;
    //
    ClientCommunicator(CommunicationManager manager, char *client_id);
    int requestOperation(QString arg, int type, int buff_len, char *resp_buff, short int *resp_type);
    //
    char *QStringToCharArray(QString str);
    int waitResponse(char *mess_buff, int buff_size, short int *m_type);
};

#endif // CLIENTCOMMUNICATOR_H

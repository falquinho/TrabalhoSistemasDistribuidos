#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include "serverbank.h"
#include <sp.h>

class Communicator
{
public:
    mailbox mbox;
    ServerBank *bank;
    ServerInfo *local_server;

    Communicator(mailbox box, ServerBank *bank, ServerInfo *local_server);
    int listen();
    void sendMessage(int size, char *message, short int flag, char *group);
    void sendAcknowledgeMess(int recipient_id);
    void sendHelloMessage(int id, int priority);
    void sendQuitMessage(int target_id);
    void voteMaster();
    void interpretMessage(int m_type, char *m_buffer);
};

#endif // COMMUNICATOR_H

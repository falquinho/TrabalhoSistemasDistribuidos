#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H
#include <sp.h>

#define MTYPE_CLIENT_REQUEST 111
#define MTYPE_SLAVE_NOTIFICATION 222
#define MTYPE_REQUEST_RESULT 333
#define MTYPE_SERVER_NOTIFICATION 444
#define MTYPE_CLIENT_NOTIFICATION 555

class CommunicationManager
{
    char *my_private_group;
    mailbox mbox;
public:
    CommunicationManager();
    //
    int openConnection(char* daemon_addr, char* my_id);
    int closeConnecion();
    //
    int joinGroup(char * group_name);
    int leaveGroup(char * group_name);
    //
    int sendMessage(const char * dest, service s_type, short int m_type, int m_len, const char *mess);
    int receiveMessage(service * s_type, char * sender, int max_groups, int * no_groups, char groups [][MAX_GROUP_NAME],\
                        short int * m_type, int * end_mm, int max_m_len, char * mess);
    //
    const char * getPrivateGroup();
    const mailbox getMailbox();
};

#endif // COMMUNICATIONMANAGER_H

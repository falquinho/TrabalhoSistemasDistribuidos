#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H
#include <sp.h>
#define CREQUEST_MKDIR 666
#define CREQUEST_MKFILE 333
#define CREQUEST_RMFILE 111
#define CREQUEST_CHDIR 55
#define CREQUEST_LIST 86
#define REQUEST_SUCCESS 999
#define REQUEST_FAILED 242

class CommunicationManager
{
public:
    mailbox mbox;
    char *private_group;
    //
    CommunicationManager();
    int connect(char* daemon_addr, char *private_name);
    int join_group(char *group_name);
    int multicast(service s_type, char *group, short int mtype, int m_len, char *mess);
    int listen(service *s_type, char* sender, int max_gr, int *no_gr, char groups[][MAX_GROUP_NAME], short int *m_type, int *end_mm, int mess_len, char* mess);
    int close_connection();
};

#endif // COMMUNICATIONMANAGER_H

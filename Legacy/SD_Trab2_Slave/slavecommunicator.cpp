#include "slavecommunicator.h"
#include "errorlog.h"
#include <iostream>
using namespace std;

SlaveCommunicator::SlaveCommunicator(CommunicationManager comm)
{
    manager = comm;
}
int SlaveCommunicator::waitOrder(FSEmulator *fs){
    service s_type;
    char sender[MAX_GROUP_NAME];
    //
    int max_groups = 1;
    char groups[max_groups][MAX_GROUP_NAME];
    int no_groups;
    //
    short int m_type;
    int end_mm;
    //
    int m_len = 512;
    char mess[m_len];
    //
    while (1){
        fill(mess, mess+m_len, 0);
        cout << "Waiting for orders...\n";
        int result = manager.listen(&s_type, sender, max_groups, &no_groups, groups, &m_type, &end_mm, m_len, mess);
        if (result < 0)
            printError(result);
        else{
            cout << "Received message from " << sender << endl;
            cout << "Message body: " << mess << endl;
            switch (m_type){
            case CREQUEST_MKDIR:
                cout << "Message type: CREQUEST_MKDIR\n";
                if (fs->createDirectory(mess)==1)
                    m_type = SUCCESS_MKDIR;
                else
                    m_type = REQUEST_FAILED;
                break;
            case CREQUEST_MKFILE:
                cout << "Message type: CREQUEST_MKFILE\n";
                if (fs->createFile(mess) == 1)
                    m_type = SUCCESS_MKFILE;
                else
                    m_type = REQUEST_FAILED;
                break;
            case CREQUEST_RMFILE:
                cout << "Message type: CREQUEST_MKFILE\n";
                if (fs->removeFile(mess)==1)
                    m_type = SUCCESS_RMFILE;
                else
                    m_type = REQUEST_FAILED;
                break;
            default:
                cout << "Unknown Message Type!\n";
                m_type = REQUEST_FAILED;
            }
            //
            answerOrder(m_type, m_len, mess);
        }
    }
}

int SlaveCommunicator::answerOrder(short int m_type, int mess_len, char *mess){
    int result = manager.multicast(RELIABLE_MESS, "SERVERS", m_type, mess_len, mess);
    if (result < 0)
        printError(result);
    return result;
}

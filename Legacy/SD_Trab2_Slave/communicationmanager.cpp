#include "communicationmanager.h"
#include "errorlog.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

CommunicationManager::CommunicationManager()
{
    private_group = (char*)malloc(MAX_GROUP_NAME);
}

int CommunicationManager::connect(char *daemon_addr, char *private_name){
    int result = SP_connect(daemon_addr, private_name, 1, 1, &mbox, private_group);

    if (result == ACCEPT_SESSION){
        cout << "Connected to the Spread Daemon!\n";
    }
    else {
        cout << "Failed to connect: ";
        printError(result);
    }
    return result;
}

int CommunicationManager::join_group(char *group_name){
    int result = SP_join(mbox, group_name);
    //
    if (result == 0)
        cout << "Succesfully joined group "<< group_name << endl;
    else
        printError(result);
    //
    return result;
}

int CommunicationManager::multicast(service s_type, char *group, short int mtype, int m_len, char *mess){
    int result = SP_multicast(mbox, s_type, group, mtype, m_len, mess);
    if (result < 0)
        printError(result);
    //
    return result;
}

int CommunicationManager::listen(service *s_type, char *sender, int max_gr, int *no_gr, char groups[][MAX_GROUP_NAME], short *m_type, int *end_mm, int mess_len, char *mess){
    int result = SP_receive(mbox, s_type, sender, max_gr, no_gr, groups, m_type, end_mm, mess_len, mess);
    if (result < 0)
        printError(result);
    //
    return result;
}

int CommunicationManager::close_connection(){
    int result = SP_disconnect(mbox);
    //
    if (result == 0)
        cout << "Disconnected from Spread Daemon!\n";
    else
        printError(result);
    //
    return result;
}

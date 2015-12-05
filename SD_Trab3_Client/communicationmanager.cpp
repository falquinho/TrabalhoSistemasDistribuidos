#include "communicationmanager.h"
#include "errorlog.h"
#include <iostream>

CommunicationManager::CommunicationManager()
{
    my_private_group = new char [MAX_GROUP_NAME];
}

int CommunicationManager::openConnection(char *daemon_addr, char *my_id)
{
    int result = SP_connect(daemon_addr, my_id, 1, 1, &mbox, my_private_group);

    if (result == ACCEPT_SESSION){
        std::cout << "CommunicationManager::openConnection successfull!\n";
    }
    else {
        std::cout << "CommunicationManager::openConnection failed...";
        printError(result);
    }
    return result;
}
//
int CommunicationManager::closeConnecion()
{
    delete [] my_private_group;
    int result = SP_disconnect(mbox);
    //
    if (result == 0)
        std::cout << "CommunicationManager::closeConnection successfull!\n";
    else
    {
        std::cout << "CommunicationManager::closeConnection failed...";
        printError(result);
    }
    //
    return result;
}
//
int CommunicationManager::joinGroup(char * group_name)
{
    int result = SP_join(mbox, group_name);
    //
    if (result == 0)
        std::cout << "CommunicationManager::joinGroup successfull!\n";
    else
    {
        std::cout << "CommunicationManager::joinGroup failed...";
        printError(result);
    }
    //
    return result;
}
//
int CommunicationManager::leaveGroup(char * group_name)
{
    int result = SP_leave(mbox, group_name);
    //
    if (result == 0)
        std::cout << "CommunicationManager::leaveGroup successfull!\n";
    else
    {
        std::cout << "CommunicationManager::leaveGroup failed...";
        printError(result);
    }
    //
    return result;
}
//
int CommunicationManager::sendMessage(const char * dest, service s_type, short int m_type, int m_len, const char *mess)
{
    int result = SP_multicast(mbox, s_type, dest, m_type, m_len, mess);
    //
    if (result >= 0)
        std::cout << "CommunicationManager::sendMessage successful!\n";
    else
    {
        std::cout << "CommunicationManager::sendMessage failed...";
        printError(result);
    }
    //
    return result;
}
//
int CommunicationManager::receiveMessage(service * s_type, char * sender, int max_groups, int * no_groups,\
                                         char groups [][MAX_GROUP_NAME], short int * m_type, int * end_mm, int m_len, char * mess)
{
    int result = SP_receive(mbox, s_type, sender, max_groups, no_groups, groups, m_type, end_mm, m_len, mess);
    if (result >= 0)
        std::cout << "CommunicationManager::receiveMessage successfull!\n";
    else
    {
        std::cout << "CommunicationManager::receiveMessage failed...";
        printError(result);
    }
    //
    return result;
}

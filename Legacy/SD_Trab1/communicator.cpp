#include <iostream>
#include "communicator.h"
#include "usefuldefines.h"

using namespace std;

Communicator::Communicator(mailbox box, ServerBank *bank, ServerInfo *local_server)
{
    cout << "Communicator is starting!\n";
    mbox = box;
    this->local_server = local_server;
    this->bank = bank;
    bank->addServer(local_server->id, local_server->priority);
}

int Communicator::listen(){
    //preparing storage variables
    service type = DROP_RECV;
    char sender[MAX_GROUP_NAME];
    int no_groups, endian_mm;
    short int m_type;
    char groups[MAX_NO_SERVERS][MAX_GROUP_NAME];
    //
    short int buffer_size = 64;
    char m_buffer[buffer_size];
    //
    cout << "Listening for messages...\n";
    //this shoud block:
    int result = SP_receive(mbox, &type, sender, MAX_NO_SERVERS, &no_groups, groups, &m_type, &endian_mm, buffer_size, m_buffer);
    if (result < 0){
        cout << "Fail to receive message! Code " << result << endl;
        return result;
    }
    //
    if (m_type == MTYPE_QUIT){
        int target_id = *m_buffer;
        if (target_id == local_server->id){
            cout << "I should quit!\n";
            return 0;
        }
    }
    //
    interpretMessage(m_type, m_buffer);
    //
    return 1;
}

void Communicator::sendMessage(int size, char *message, short int flag, char *group){
    cout << "Sending message of size " << size << " to group " << group << endl;
    //
    int result = SP_multicast(mbox, SAFE_MESS, group, flag, size, message);
    if (result == ILLEGAL_SESSION || result == ILLEGAL_MESSAGE || result == CONNECTION_CLOSED){
        cout << "Failed to deliver message!\n";
    }
    else
        cout << "Message delivered!\n";
}

void Communicator::sendAcknowledgeMess(int recipient_id){
    cout << "Sending Acknowledgment message to Server ID " << recipient_id << endl;
    int m_size = sizeof(int)*3;
    char m_buffer[m_size];
    m_buffer[0] = local_server->id;
    m_buffer[sizeof(int)-1] = local_server->priority;
    m_buffer[(2*sizeof(int))-1] = recipient_id;
    //
    sendMessage(m_size, m_buffer, MTYPE_ACKNOWLEDGE, GROUP_NAME);
}

void Communicator::sendHelloMessage(int id, int priority){
    cout << "Sending a HELLO message...\n";
    //
    int m_size = 2*sizeof(int);
    char m_buffer[m_size];
    m_buffer[0] = id;
    m_buffer[sizeof(int)-1] = priority;
    sendMessage(m_size, m_buffer, MTYPE_HELLO, GROUP_NAME);
}

void Communicator::sendQuitMessage(int target_id){
    int m_size = sizeof(int);
    char m_buffer[m_size];
    m_buffer[0] = target_id;
    sendMessage(m_size, m_buffer, MTYPE_QUIT, GROUP_NAME);
}

void Communicator::voteMaster(){
    cout << "Sending vote for Master.\n";
    int m_size = sizeof(int)*2;
    char m_buffer[m_size];
    m_buffer[0] = bank->master.id;
    m_buffer[sizeof(int)-1] = bank->master.priority;
    //
    sendMessage(m_size, m_buffer, MTYPE_MASTER_VOTE, GROUP_NAME);
}

void Communicator::interpretMessage(int m_type, char *m_buffer){
    int id = *m_buffer;
    int prio = *(m_buffer + sizeof(int)-1);
    //
    if (m_type == MTYPE_ACKNOWLEDGE && id != local_server->id){
            int recipient_id = *(m_buffer + 2*sizeof(int)-1);
            cout << "Received an ACKNOWLEDGE message to recipient with ID " << recipient_id << endl;
            if (recipient_id == local_server->id){
                cout << "Thats me!\n";
                int result = bank->addServer(id, prio);
            }
    }
    //
    if (m_type == MTYPE_HELLO && id != local_server->id){
        cout << "Received a HELLO message!\n";
        int result = bank->addServer(id, prio);
        //
        if (result == 1) {
            cout << "Responding with an ACKNOWLEDGE message!\n";
            sendAcknowledgeMess(id);
        }
        else if (result == 0) {
            cout << "Notifying the new Server he should quit!\n";
            sendQuitMessage(id);
        }
    }
    //
    if (m_type == MTYPE_MASTER_VOTE){
        int candidate_id, candidate_prio;
        //
        if (candidate_id >= 0){
            if (candidate_prio > bank->master.priority) {
                bank->addServer(candidate_id, candidate_prio);
            }
        }
    }
    //
}

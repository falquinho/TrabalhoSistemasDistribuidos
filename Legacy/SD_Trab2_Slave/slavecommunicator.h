#ifndef SLAVECOMMUNICATOR_H
#define SLAVECOMMUNICATOR_H
#include "communicationmanager.h"
#include "fsemulator.h"

class SlaveCommunicator
{
public:
    CommunicationManager manager;
    //
    SlaveCommunicator(CommunicationManager comm);
    int waitOrder(FSEmulator *fs);
    int answerOrder(short int m_type,int mess_len,  char *mess);
};

#endif // SLAVECOMMUNICATOR_H

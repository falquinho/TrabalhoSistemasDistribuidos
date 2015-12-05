#ifndef ELECTIONSYSTEM_H
#define ELECTIONSYSTEM_H
#include "communicationmanager.h"
#include <qdatetime.h>
#include <sp.h>

class ElectionSystem
{
public:
    char *my_id;
    bool isVoting;
    int quitters;
    int no_particiants;
    bool election_ongoing;
    QDateTime datetime;
    //
    ElectionSystem();
    int startElection(char *private_name, int no_participants, QDateTime process_age);
    bool amIweaker(char *mess);
    bool isFinished();
};

#endif // ELECTIONSYSTEM_H

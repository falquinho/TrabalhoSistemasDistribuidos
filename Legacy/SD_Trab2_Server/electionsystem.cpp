#include "electionsystem.h"
#include <iostream>
#include <stdlib.h>
#include "errorlog.h"
using namespace std;

ElectionSystem::ElectionSystem()
{
    election_ongoing = false;
    isVoting = false;
}

int ElectionSystem::startElection(char *private_name, int no_participants, QDateTime process_age){
    quitters = 0;
    election_ongoing = true;
    isVoting = false;
    my_id = private_name;
    this->no_particiants = no_participants;
    datetime = process_age;
}

bool ElectionSystem::amIweaker(char *mess){
    QString mess_str(mess);
    QDateTime oponent = QDateTime::fromString(mess_str);
    if (oponent > datetime)
        return 1;
    return 0;
}

bool ElectionSystem::isFinished(){
    if (quitters >= no_particiants-1)
        return true;
    else
        return false;
}

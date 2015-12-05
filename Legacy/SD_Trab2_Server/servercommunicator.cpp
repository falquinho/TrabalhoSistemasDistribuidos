#include "servercommunicator.h"
#include "errorlog.h"
#include <qstring.h>
#include <qstringlist.h>
#include <iostream>
using namespace std;

ServerCommunicator::ServerCommunicator(CommunicationManager manager)
{
    this->manager = manager;
    coordinator = false;
}

int ServerCommunicator::listenLoop(){
    char sender[MAX_GROUP_NAME];
    service s_type = DROP_RECV;
    int no_groups;
    //
    int max_groups = 32;
    char groups[max_groups][MAX_GROUP_NAME];
    //
    short int m_type;
    int end_mm;
    //
    int m_len = 512;
    char mess[m_len];
    //
    while (1){
        fill(mess, mess + m_len, 0);
        //
        int result = manager.listen(&s_type, sender, max_groups, &no_groups, groups, &m_type, &end_mm, m_len, mess);
        if (result < 0){
            cout << "TODO deal with listen errors @ ServerCommunicator::listenLoop()\n";
            printError(result);
            //deal with error
        }
        else {
            elections.no_particiants = no_groups;
            //
            cout << "Received message from " << sender << endl;
            cout << "Message: "<< mess << endl;
            //
            if (Is_reg_memb_mess(s_type) && !coordinator && !elections.election_ongoing){
                cout << "Message type: REG_MEMB_MESS\n";
                cout << "Votation will start!\n";
                elections.startElection(manager.private_group, no_groups, QDateTime::currentDateTime());
                elections.isVoting = false;
                //
                if (elections.no_particiants <= 1){
                    m_type = ELECTION_QUIT;
                    elections.isVoting = true;
                }
                else
                    m_type = ELECTION_START;
            }
            cout << m_type << endl;
            cout << elections.isVoting << endl;
            //
            switch (m_type){
            case ELECTION_START: {
                if (elections.isVoting) break;
                //
                cout << "Entering election!\n";
                elections.isVoting = true;
                QString str = elections.datetime.toString();
                char *my_vote = str.toLocal8Bit().data();
                int vote_size = str.size();
                cout << "My vote: "<< my_vote << endl;
                manager.multicast(RELIABLE_MESS, "SERVERS", ELECTION_VOTE, vote_size, my_vote);
                break;
            }
            case ELECTION_VOTE:
                if (!elections.isVoting) break;
                //
                if (elections.amIweaker(mess)){
                    cout << "I cant win.. Quiting!\n";
                    elections.isVoting = false;
                    manager.multicast(RELIABLE_MESS, "SERVERS", ELECTION_QUIT, 0, 0);
                }
                break;
            case ELECTION_QUIT:
                if (!elections.isVoting) break;
                //
                elections.quitters ++;
                if (elections.isFinished()){
                    cout << "Elections must die!\n";
                    QString str (manager.private_group);
                    manager.multicast(RELIABLE_MESS, "SERVERS", ELECTION_FINISH, str.size(), manager.private_group);
                }
                break;
            case ELECTION_FINISH:{
                cout << "Elections are over!\n";
                elections.election_ongoing = false;
                //
                if (elections.isVoting && elections.isFinished()){
                    cout << "I won the election!\n";
                    coordinator = true;
                }
                else
                    coordinator = false;
                break;
            }
            case CREQUEST_MKDIR:
                cout << "Its a mkdir request!\n";
                sendOrder(sender, m_type, mess);
                break;
            case CREQUEST_MKFILE:
                cout << "It's a mkfile request!\n";
                sendOrder(sender, m_type, mess);
                break;
            case CREQUEST_RMFILE:
                cout << "It's a rmfile request!\n";
                sendOrder(sender, m_type, mess);
                break;
            case SUCCESS_MKDIR:
                cout << "TODO: add dir to directory structure\n";
                if (coordinator)
                    manager.multicast(RELIABLE_MESS, extractClient(mess), REQUEST_SUCCESS, 0, 0);
                break;
            case SUCCESS_MKFILE:
                cout << "TODO: add file to directory structure\n";
                if (coordinator)
                    manager.multicast(RELIABLE_MESS, extractClient(mess), REQUEST_SUCCESS, 0, 0);
                break;
            case SUCCESS_RMFILE:
                cout << "TODO: remove file frm directory structure\n";
                if (coordinator)
                    manager.multicast(RELIABLE_MESS, extractClient(mess), REQUEST_SUCCESS, 0, 0);
                break;
            case REQUEST_FAILED:
                cout << "Request by client "<< extractClient(mess) <<" failed!\n";
                if (coordinator)
                    manager.multicast(RELIABLE_MESS, extractClient(mess), REQUEST_FAILED, 0, 0);
                break;
            default:
                cout << "Unknown message...\n";
            }
        }
    }
}

char *ServerCommunicator::extractClient(char *mess){
    QString str (mess);
    QStringList ls = str.split("/", QString::SkipEmptyParts);
    str = ls.at(0);
    char * client = str.toLocal8Bit().data();
    cout << "The Client wich requested this was " << client << endl;
    return client;
}

int ServerCommunicator::sendOrder(char *client, short int m_type, char *mess){
    cout << "Preparing order to send to slaves...\n";
    QString str(client);
    str.append("/"); str.append(mess);
    //
    char *mess_comp = str.toLocal8Bit().data();
    cout << "Sending order: "<< mess << endl;
    //
    int result = manager.multicast(RELIABLE_MESS, "SLAVES", m_type, str.size(), mess_comp);
    if (result < 0)
        printError(result);
    return result;
}

#ifndef SERVERBANK_H
#define SERVERBANK_H
#include <vector>
#include "serverinfo.h"
using namespace std;

class ServerBank
{
public:
    vector<ServerInfo> bank;
    int capacity;
    ServerInfo master;

    ServerBank(int capacity);
    int addServer(int id, int priority);
    int addServer(ServerInfo server);
    int removeServer(int serverID);
    void updateMaster();
    void printList();
};

#endif // SERVERBANK_H

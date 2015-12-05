#include "serverbank.h"
#include <iostream>
using namespace std;

ServerBank::ServerBank(int capacity)
{
    this->capacity = capacity;
}

int ServerBank::addServer(ServerInfo server){
    removeServer(server.id);
    bank.push_back(server);
    return 1;
}

int ServerBank::addServer(int id, int priority){
    cout << "Adding server with id " << id << " to the bank...\n";
    if (bank.size() >= capacity){
        cout << "Unable to add new Server. Max capacity reached!\n";
        return 0;
    }
    ServerInfo server(id, priority, "", "");
    addServer(server);
    cout << "Server added!\n";
    updateMaster();
    printList();
    //
    return 1;
}

int ServerBank::removeServer(int serverID){
    cout <<"Removing Server with id "<< serverID << endl;
    int i;
    for (i=0; i<bank.size(); i++){
        if (bank.at(i).id == serverID){
            bank.erase(bank.begin()+i);
        }
    }
    updateMaster();
    printList();
    return 1;
}

void ServerBank::updateMaster(){
    if (bank.size() == 0){
        master.id = -1;
        master.priority = -1;
    }
    else if (bank.size() >=1){
        master = bank.at(0);
        int i;
        for (i=1; i<bank.size(); i++){
            if ((bank.at(i)).priority > master.priority)
                master = bank.at(i);
        }
    }
}

void ServerBank::printList(){
    cout << "Master Server:\n";
    cout << "{\nid = "<< master.id<<endl<<"prority = "<<master.priority<<endl;
    cout << "}\n";
    cout << "Known Servers:\n";
    int i;
    for (i=0; i<bank.size(); i++){
        ServerInfo curr = bank.at(i);
        cout << "{\nid = " << curr.id << endl;
        cout << "priority = " << curr.priority << endl;
        cout << "address = " << curr.ipaddr << endl;
        cout << "port = " << curr.port << "\n}\n";
    }
}


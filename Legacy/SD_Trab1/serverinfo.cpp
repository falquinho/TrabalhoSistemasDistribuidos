#include "serverinfo.h"

ServerInfo::ServerInfo(){
    //
}

ServerInfo::ServerInfo(int id, int prio, char *addr, char *port){
    this->id = id;
    this->priority = prio;
    this->ipaddr = addr;
    this->port = port;
}

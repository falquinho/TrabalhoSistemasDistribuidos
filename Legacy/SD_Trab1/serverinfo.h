#ifndef SERVERINFO_H
#define SERVERINFO_H

class ServerInfo
{
public:
    int id;
    int priority;
    char *ipaddr;
    char *port;
    ServerInfo();
    ServerInfo(int id, int prio, char *addr, char*port);
};

#endif // SERVERINFO_H

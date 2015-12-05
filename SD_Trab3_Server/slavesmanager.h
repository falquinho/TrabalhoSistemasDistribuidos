#ifndef SLAVESMANAGER_H
#define SLAVESMANAGER_H
#include <string>
#include <vector>
typedef std::string String;

class SlavesManager
{
    std::vector<String> slaves;
    unsigned int index;
public:
    SlavesManager();
    int registerSlave(String slave_id);
    int removeSlave(String slave_id);
    String getNextSlave();
    int noOfSlaves();
};

#endif // SLAVESMANAGER_H

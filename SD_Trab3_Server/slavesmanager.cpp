#include "slavesmanager.h"
#include <iostream>

SlavesManager::SlavesManager():
    index(0)
{
    //
}

int SlavesManager::registerSlave(String slave_id)
{
    std::cout << "SlavesManager::registerSlave" << std::endl;
    int i;
    for (i=0; i<slaves.size(); i++)
    {
        if (slaves.at(i) == slave_id)
            return 0;
    }
    //
    slaves.push_back(slave_id);
    return 1;
}

int SlavesManager::removeSlave(String slave_id)
{
    std::cout << "SlavesManager::removeSlave" << std::endl;
    int i;
    for (i=0; i<slaves.size(); i++)
    {
        if (slaves.at(i) == slave_id)
        {
            slaves.erase(slaves.begin()+i);
            return 1;
        }
    }
    return 0;
}

String SlavesManager::getNextSlave()
{
    std::cout << "SlavesManager::getNextSlave" << std::endl;
    //
    if (index >= slaves.size())
        index = 0;
    index ++;
    return slaves.at(index-1);
}

int SlavesManager::noOfSlaves(){
    //std::cout << "SlavesManager::noOfSlaves" << std::endl;
    return slaves.size();
}

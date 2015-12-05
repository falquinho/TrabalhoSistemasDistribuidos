#include "resourcemanager.h"
#include <iostream>

int ResourceManager::addResource(String name, String location)
{
    std::cout  << "ResourceManager::addResource:";
    if (!exists(name))
    {
        std::cout << "new resource added!\n";
        Resource new_res;
        new_res.name = name;
        new_res.lock = false;
        new_res.location.push_back(location);
        //
        resource_register.push_back(new_res);
        return 1;
    }
    else
    {
        std::cout << "adding location to existing resource\n";
        int i;
        for (i=0; resource_register.at(i).name != name; i++);
        //
        resource_register.at(i).location.push_back(location);
        return 1;
    }
}

int ResourceManager::removeResource(String name)
{
    std::cout << "ResourceManager::removeResource: ";
    if (!exists(name))
    {
        std::cout << "resource does not exists!\n";
        return 0;
    }
    else
    {
        int i;
        for (i=0; resource_register.at(i).name != name; i++);
        resource_register.erase(resource_register.begin()+i);
        return 1;
    }
}

int ResourceManager::removeLocation(String location)
{
    std::cout << "ResourceManager::removeLocation" << std::endl;

    int i, j;
    for (i=0; i<resource_register.size(); i++)
    {
        Resource & r = resource_register.at(i);
        for (j=0; j<r.location.size(); j++)
        {
            if (r.location.at(j) == location)
            {
                r.location.erase(r.location.begin()+j);
            }
        }
    }
    return 1;
}

Resource ResourceManager::getResource(String resource)
{
    std::cout << "ResourceManager::getResource: ";
    int i;
    for (i=0; i < resource_register.size(); i++)
    {
        Resource current = resource_register.at(i);
        if (current.name == resource)
        {
            std::cout << "returning resource!\n";
            return current;
        }
    }
    std::cout << "resource not found! returning 'error' resource\n";
    Resource r;
    r.name = "error";
    return r;
}

bool ResourceManager::lockResource(String resource)
{
    int i;
    for (i=0; i<resource_register.size(); i++)
    {
        Resource & res = resource_register.at(i);
        if (res.name == resource)
        {
            res.lock = true;
            return true;
        }
    }
    return false;
}

bool ResourceManager::unlockResource(String resource)
{
    int i;
    for (i=0; i<resource_register.size(); i++)
    {
        Resource & res = resource_register.at(i);
        if (res.name == resource)
        {
            res.lock = false;
            return true;
        }
    }
    return false;
}

bool ResourceManager::isLocked(String resource)
{
    int i;
    for (i=0; i<resource_register.size(); i++)
    {
        Resource curr = resource_register.at(i);
        if (curr.name == resource)
            return curr.lock;
    }
}

bool ResourceManager::exists(String resource)
{
    int i;
    for (i=0; i<resource_register.size(); i++)
    {
        if (resource_register.at(i).name == resource)
            return true;
    }
    return false;
}

void ResourceManager::printResources()
{
    unsigned int i;
    for (i=0; i<resource_register.size(); i++)
    {
        Resource curr_res = resource_register.at(i);
        std::cout << "'" << curr_res.name << "'\n";
        //
        if (curr_res.lock)
            std::cout << "Locked!\n";
        else
            std::cout << "Not locked!\n";
        //
        std::cout << "\t";
        unsigned int j;
        for (j=0; j<curr_res.location.size(); j++)
        {
            std::cout << curr_res.location.at(j) << " | ";
        }
        std::cout << "\n";
    }
}

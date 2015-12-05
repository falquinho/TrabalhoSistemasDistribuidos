#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <string>
#include <vector>
typedef std::string String;

struct Resource{
    String name;
    bool lock;
    std::vector<String> location;
};

class ResourceManager
{
    std::vector<Resource> resource_register;
public:
    int addResource(String name, String location);
    int removeResource(String name);
    int removeLocation(String location);
    Resource getResource(String resource);
    bool lockResource(String resouce);
    bool unlockResource(String resource);
    bool isLocked(String resource);
    bool exists(String resource);
    void printResources();
};

#endif // RESOURCEMANAGER_H

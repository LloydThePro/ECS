#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include <iostream>
#include <vector>
#include "Types.h"
#include "EntityCreator.h"



class ComponentManager{

public:

    static ComponentID registerComp(uint32_t compSize);
    static void * queryComponentMemory(ComponentID comID);
    static bool isComponentValid(ComponentID id);
    static unsigned int allocMem(ComponentID id);
private:
    static ComponentID ids;
    static std::vector<Component> registeredComp;



};

#endif // COMPONENTMANAGER_H

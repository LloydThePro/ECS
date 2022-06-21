#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include <iostream>
#include <vector>
#include "Types.h"
#include "ErrorHandling.h"


class ComponentManager{

public:

    static ComponentID registerComp(uint32_t compSize);
    static void * queryComponentMemory(MemOwnership memOwn);
    static bool isComponentValid(ComponentID id);
    static OwnershipID allocMem(ComponentID id);
    



private:
    static ComponentID ids;
    static std::vector<Component> registeredComp;



};



#endif // COMPONENTMANAGER_H


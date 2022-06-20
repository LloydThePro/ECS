#include "ComponentManager.h"

int ComponentManager::registerComp(uint32_t compSize){

        Component temp;
        temp.id = ids;
        temp.memory.push_back(nullptr);
        temp.comSize = compSize;
        registeredComp.push_back(temp);
        return ids++;
}

void * ComponentManager::queryComponentMemory(ComponentID comID){

        for(Component c : registeredComp){
            if(c.id == comID){
                return c.memory.data();
            }
        }

        return nullptr;
}

bool ComponentManager::isComponentValid(ComponentID id){

    for(Component c : registeredComp){
        if(c.id == id){
            return true;
        }
    }
    return false;
}

unsigned int ComponentManager::allocMem(ComponentID id){

    for(Component c : registeredComp){
        if(c.id == id){
            c.memory.push_back((void *)new char[c.comSize]);
            return c.memory.size() - 1;
        }
    }

    return 0;// again need some proper failure handling
}

ComponentID ComponentManager::ids = 0;
std::vector<Component> ComponentManager::registeredComp;


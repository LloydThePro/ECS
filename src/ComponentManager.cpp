#include "../include/ComponentManager.h"
#include "../include/ErrorHandling.h"
ComponentID ComponentManager::registerComp(uint32_t compSize){
        
        if (compSize == 0) {
            ECS::ErrorHandling::logError("component size is 0", "ComponenManager", "int ComponentManager::registerComp(uint32_t compSize)", 6);
        }
        
        Component temp;
        temp.id = ids;
        temp.memory.push_back(nullptr);
        temp.comSize = compSize;
        registeredComp.push_back(std::move(temp));
        return ids++;
}

void * ComponentManager::queryComponentMemory(ComponentID comID){

        for(Component c : registeredComp){
            if(c.id == comID){
                return c.memory.data();
            }
        }

        ECS::ErrorHandling::logError("component was not found", "ComponenManager", "void * ComponentManager::queryComponentMemory(ComponentID comID)", 25);
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

            void* mem = reinterpret_cast<void*>(new char[c.comSize]);
            if (mem == nullptr) { 
                ECS::ErrorHandling::logError("Memory Allocation Fail","ComponentManager", "void* mem = reinterpret_cast<void*>(new char[c.comSize]);", 47);
                return 0; 
            } 

            c.memory.push_back((void *)new char[c.comSize]);
            return c.memory.size() - 1;
        }
    }
    ECS::ErrorHandling::logError("Component was not found", "ComponentManager", "ComponentManager::allocMem(ComponentID id)", 55);

    return 0;
}

ComponentID ComponentManager::ids = 0;
std::vector<Component> ComponentManager::registeredComp;


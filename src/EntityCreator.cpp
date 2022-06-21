#include "../include/EntityCreator.h"
#include "../include/ErrorHandling.h"
EntityCreator::EntityCreator()
{
    //ctor
}

EntityObj EntityCreator::createEntity(EntityID entID){

    if (!EntityManager::isEntityValid(entID)) {

        ECS::ErrorHandling::logError("Invalid Entity", "EntityCreator", "EntityCreator::createEntity", 8);
        return EntityObj(); 
    }

    for(const Entity& e : EntityManager::registeredEnt){

        if(e.id == entID){
            EntityObj obj;
            obj.entType = entID;

            for(const ComponentID& i : e.compBind){
                MemOwnership ownership;
                ownership.ownID = ComponentManager::allocMem(i);
                ownership.compID = i;
                obj.memLoc.push_back(ownership);

            }
            return std::move(obj);
            break;
        }

    }

    ECS::ErrorHandling::logError("Entity was not found", "EntityCreator", "EntityCreator::createEntity", 35);
    return EntityObj();
}

void * EntityCreator::getComponent(const EntityObj& entObj, ComponentID comID){

    if(!EntityManager::isEntityValid(entObj.entType) || !ComponentManager::isComponentValid(comID))return nullptr;

    for(const MemOwnership& o : entObj.memLoc){
        if(o.compID == comID){
            
            return ComponentManager::queryComponentMemory(o);
        }
    }
   
    ECS::ErrorHandling::logError("Component was not found", "EntityCreator", "EntityCreator::getComponent", 49);
    return nullptr;

}




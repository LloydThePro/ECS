#include "EntityCreator.h"

EntityCreator::EntityCreator()
{
    //ctor
}

EntityObj EntityCreator::createEntity(EntityID entID){

    if(!EntityManager::isEntityValid(entID))return EntityObj(); // need some proper error handling here

    for(Entity& e : EntityManager::registeredEnt){

        if(e.id == entID){
            EntityObj obj;
            obj.entType = entID;

            for(ComponentID i : e.compBind){
                MemOwnership ownership;
                ownership.ownID = ComponentManager::allocMem(i);
                ownership.compID = i;
                obj.memLoc.push_back(ownership);

            }
            return std::move(obj);
            break;
        }

    }

}

void * EntityCreator::getComponent(const EntityObj& entObj, ComponentID comID){

    if(!EntityManager::isEntityValid(entObj.entType) || !ComponentManager::isComponentValid(comID))return nullptr;

    for(MemOwnership o : entObj.memLoc){
        if(o.compID == comID){
            return ComponentManager::queryComponentMemory(comID);
        }
    }

   return nullptr;

}



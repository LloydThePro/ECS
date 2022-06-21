#include "../include/EntityManager.h"
#include "../include/ErrorHandling.h"
EntityID EntityManager::ids = 0;
std::vector<Entity> EntityManager::registeredEnt;
EntityManager::EntityManager()
{
    //ctor
}

EntityID EntityManager::registerEntity(){

    Entity ent;
    ent.id = ids;
    EntityManager::registeredEnt.push_back(std::move(ent));


    return EntityManager::ids++;
}

void EntityManager::BindComponentToEnt(EntityID entID, ComponentID compID){

    bool isValid = isEntityValid(entID) && ComponentManager::isComponentValid(compID);

    if(!isValid){
        // do some error handling here probably use some throws
        ECS::ErrorHandling::logError("Invalid Entity or Component ID", "EntityManager", "EntityManager::BindComponentToEnt", 24);
        return;
    }


    for(Entity& e : EntityManager::registeredEnt){

        if(e.id == entID){


            bool isAlreadyBind = false;

            for(const ComponentID& r : e.compBind){
                if(r == compID){
                    isAlreadyBind = true;
                    break;
                }
            }
            if(!isAlreadyBind)
                e.compBind.push_back(compID);
        }
    }

}
bool EntityManager::isEntityValid(EntityID id){

    for(const Entity& e : EntityManager::registeredEnt){
        if(e.id == id)return true;
    }

    return false;
}

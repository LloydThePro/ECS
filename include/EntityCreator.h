#ifndef ENTITYCREATOR_H
#define ENTITYCREATOR_H
#include "Types.h"
#include "ErrorHandling.h"
#include "EntityManager.h"
#include "ComponentManager.h"



class EntityCreator
{
    public:
        EntityCreator();
        static EntityObj createEntity(EntityID entID);
        static void * getComponent(const EntityObj& entObj, ComponentID comID);
        



    protected:

    private:
};






#endif // ENTITYCREATOR_H

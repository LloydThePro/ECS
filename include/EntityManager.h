#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <vector>
#include "ComponentManager.h"
#include "EntityCreator.h"
#include "Types.h"

class EntityManager
{
    public:
        EntityManager();
        static EntityID registerEntity();
        static void BindComponentToEnt(EntityID, ComponentID);
        static bool isEntityValid(EntityID id);
    protected:

    private:
        static EntityID ids;
        static std::vector<Entity> registeredEnt;
        friend class EntityCreator;
};



#endif // ENTITYMANAGER_H

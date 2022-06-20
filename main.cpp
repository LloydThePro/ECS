#include <iostream>
#include "include/ComponentManager.h"
#include "include/EntityManager.h"


typedef struct{
    int x, y;
}Pos;

typedef struct{
    float x, y;
}PosF;


static  ComponentID posID = ComponentManager::registerComp(sizeof(Pos));
static  ComponentID posFID = ComponentManager::registerComp(sizeof(PosF));
static EntityID Person = EntityManager::registerEntity();
static EntityID People = EntityManager::registerEntity();

int main(){


    EntityManager::BindComponentToEnt(Person, posID);



    EntityObj someGuy = EntityCreator::createEntity(Person);

    Pos * myPosPtr = reinterpret_cast<Pos *>(EntityCreator::getComponent(someGuy, posID));

    myPosPtr->x = 5;
    myPosPtr->y = 5;




    return 0;
}

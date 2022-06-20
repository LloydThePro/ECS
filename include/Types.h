#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED
#include <stdint.h>
#include <vector>
typedef uint32_t OwnershipID;
typedef uint32_t EntityID;
typedef uint32_t ComponentID;

typedef struct{
    ComponentID id;
    std::vector<void *> memory;
    uint32_t comSize;
}Component;

typedef struct{
    OwnershipID ownID;
    ComponentID compID;
}MemOwnership;

typedef struct {
    std::vector<MemOwnership> memLoc;
    EntityID entType;
}EntityObj;



typedef struct{
    EntityID id;
    std::vector<ComponentID> compBind; // binded components
}Entity;


#endif // TYPES_H_INCLUDED

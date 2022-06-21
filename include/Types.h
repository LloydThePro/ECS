#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED
#include <stdint.h>
#include <vector>
#include <string>

typedef uint32_t OwnershipID;
typedef uint32_t EntityID;
typedef uint32_t ComponentID;

constexpr auto INVALID_ENTITY_OBJ = nullptr;


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


namespace ECS{

    typedef struct {
        uint32_t lineNum;
        std::string message;
        std::string logInfo;
    }ErrorInfo;


    template<typename T> T* getProperType(void * memStruct) {

        T* ret = reinterpret_cast<T*>(memStruct);
        ret = new(ret)T;
        return ret;
    }

}

#endif // TYPES_H_INCLUDED

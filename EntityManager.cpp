#include "EntityManager.h"

becs::EntityID EntityManager::registerEntity(bool* isThisRealloc) {


    if (!m_deletedEnt.empty()) {
        becs::EntityID id = m_deletedEnt.front();
        m_deletedEnt.pop();
        m_isActive[id] = true;
        *isThisRealloc = true;
        return id;
    }

    becs::EntityID id = m_counter;
    m_isActive.push_back(true);
    becs::Entity ent;
    ent.entID = id;
    m_entities.emplace_back(ent);
    *isThisRealloc = false;
    m_counter++;
    return id;
}

bool EntityManager::doesExist(becs::EntityID entID) {
    if (entID >= m_counter)return false;

    return m_isActive[entID];
}

void EntityManager::bindComponentToEnt(becs::EntityID entID, becs::ComponentID compID) {
    if(!doesExist(entID))return;

    
    for (const becs::ComponentID& c : m_entities[entID].bindedComponents) {

        if (c == compID) {
           
            return;
        }
    }

    m_entities[entID].bindedComponents.push_back(compID);
    

}

void EntityManager::unbindAllComponents(becs::EntityID entID) {
    m_entities[entID].bindedComponents.clear();
}

void EntityManager::unregisterEntity(becs::EntityID entID) {
   
    if (!doesExist(entID))return;

    unbindAllComponents(entID);
    m_deletedEnt.push(entID);
    m_isActive[entID] = false;
}

size_t EntityManager::getEntityCapacity() {
    return m_entities.size();
}

size_t EntityManager::getEntityCount() {
    return m_entities.size() - m_deletedEnt.size();
}

const std::vector<becs::ComponentID>& EntityManager::getComponentBounded(becs::EntityID entID)
{
    if (doesExist(entID))return m_entities[entID].bindedComponents;

    return std::vector<becs::ComponentID>();
}

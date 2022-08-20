#include "EntityManager.h"

becs::EntityID EntityManager::registerEntity() {

    becs::EntityID id = m_counter;
    m_isActive.push_back(true);
    becs::Entity ent;
    ent.entID = id;
    m_entities.emplace_back(ent);

    m_counter++;
    return id;
}

bool EntityManager::doesExist(becs::EntityID entID) {
    if (entID >= m_counter)return false;

    return m_isActive[entID];
}

void EntityManager::unregisterEntity(becs::EntityID entID) {
   
    if (!doesExist(entID))return;

    m_deletedEnt.push(entID);
    m_isActive[entID] = false;
}

size_t EntityManager::getEntityCapacity() {
    return m_entities.size();
}

size_t EntityManager::getEntityCount() {
    return m_entities.size() - m_deletedEnt.size();
}

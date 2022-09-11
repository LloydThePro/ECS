#include "ComponentFilterManager.h"

using namespace becs;

FilterID becs::ComponentFilterManager::createFilter()
{
    if (!m_deletedFilters.empty()) {

        FilterID id = m_deletedFilters.front();
        m_deletedFilters.pop();
        return id;
    }

    m_filters.push_back(becs::Filter());

    return m_filters.size() - 1;
}

void becs::ComponentFilterManager::destroyFilter(FilterID fID) {
    
    if (fID >= m_filters.size())return; // not valid iD

    m_filters[fID].components.clear();
    m_filters[fID].entities.clear();

    m_deletedFilters.push(fID);

}

void becs::ComponentFilterManager::addComponent(FilterID id, ComponentID compID) {

    if (id >= m_filters.size())return; // not valid iD

    bool isAlreadyInList = false;

    for (const auto& c : m_filters[id].components) { // check if already exist

        if (c == compID) {
            isAlreadyInList = true;
            break;
        }

    }

    
    if(!isAlreadyInList)
        m_filters[id].components.push_back(compID);
    
}

void becs::ComponentFilterManager::addComponent(FilterID id, ComponentID* compIDs, size_t count) {
    for (size_t i = 0; i < count; i++) {
        addComponent(id, compIDs[i]);
    }
}

const std::vector<EntityID>& becs::ComponentFilterManager::getEntities(FilterID filterID) {
    if (filterID >= m_filters.size()) {
        return std::move(std::vector<EntityID>());
    }
       
    return m_filters[filterID].entities;
}

const std::vector<ComponentID>& becs::ComponentFilterManager::getComponents(FilterID filterID) {
    if (filterID >= m_filters.size()) {
        return std::move(std::vector<ComponentID>());
    }

    return m_filters[filterID].components;
}


std::vector<Filter>& becs::ComponentFilterManager::getFilter() {
    return m_filters;
}
void becs::ComponentFilterManager::addEntities(FilterID id, EntityID entID) {
    if (id >= m_filters.size()) {
        return;
    }

    m_filters[id].entities.push_back(entID);

}

void becs::ComponentFilterManager::copyFilter(FilterID to, FilterID from) {

    if (to >= m_filters.size() || from >= m_filters.size())return;


    for (const auto& c : m_filters[from].components) {
        m_filters[to].components.push_back(c);          // NOTE: checking/handling duplicate not implemented
    }

}

void becs::ComponentFilterManager::addEntToFilter(FilterID id, EntityID entID) {
    
    m_filters[id].entities.push_back(entID);

}

void becs::ComponentFilterManager::removeEntity(FilterID id, EntityID entID) {
    
    uint32_t idx = 0;
    bool exist = false;
    for (const auto& e : m_filters[id].entities) {

        if (e == entID) {
            exist = true;
            break;
        }
        idx++;
    }

    if(exist)
        m_filters[id].entities.erase(m_filters[id].entities.begin() + idx);



}

void becs::ComponentFilterManager::removeEntity(EntityID entID) {
    FilterID id = 0;
    for (const auto& f : m_filters) {

        for (const auto& e : f.entities) {
            if (entID == e) {
                removeEntity(id, e);
            }
        }
        id++;
    }
}

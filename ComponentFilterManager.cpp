#include "ComponentFilterManager.h"

using namespace becs;

FilterID becs::ComponentFilterManager::createFilter()
{
    m_filters.push_back(becs::Filter());

    return m_filters.size() - 1;
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

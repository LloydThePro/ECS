#include "ComponentManager.h"

becs::ComponentID ComponentManager::registerComponent()
{
    becs::ComponentID id = m_counter;
    m_counter++;
    return id;
}

becs::ComponentID ComponentManager::getLastIndex()
{
    return m_counter - 1;
}

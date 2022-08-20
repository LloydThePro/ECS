#include "MemoryManager.h"
using namespace becs;


void MemoryManager::initEntityMemory() {

	m_indexTable.push_back(std::unordered_map<becs::ComponentID, uint32_t>());
}

void MemoryManager::initComponentMemory(size_t compSize) {
	m_componentMemory.push_back(std::move(becs::ComponentMemory(compSize)));
	
}

void MemoryManager::addComponentInstance(becs::ComponentID compID, EntityID entID) {

	m_componentMemory[compID].push_back(nullptr);
	m_indexTable[entID].insert(std::make_pair(compID, m_componentMemory[compID].getComponentCount() - 1));
}

unsigned char* becs::MemoryManager::getComponent(EntityID entID, ComponentID compID) {

	if (m_indexTable[entID].find(compID) == m_indexTable[entID].end()) {

		
		return nullptr;
	}
	uint32_t index = m_indexTable[entID].at(compID);
	return m_componentMemory[compID].get(index);

	
}

bool becs::MemoryManager::hasComponent(EntityID entID, ComponentID compID) {

	if(m_indexTable[entID].find(compID) == m_indexTable[entID].end())
		return false;

	return true;
}


#define _ENABLE_DEBUG

#ifdef  _ENABLE_DEBUG
#include <iostream>
void becs::MemoryManager::debug() {

	for (auto& c : m_componentMemory) {
		std::cout << "Component Count: " << c.getComponentCount() << " Component Size: " << c.getComponentSize() << '\n';
		for (size_t i = 0; i < c.getComponentCount(); i++) {
			std::cout << (int*)c.get(i) << ' ';
		}
		std::cout << '\n';
	}


}
#endif //  _ENABLE_DEBUG

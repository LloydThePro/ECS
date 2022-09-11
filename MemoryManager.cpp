#include "MemoryManager.h"
using namespace becs;


void MemoryManager::initEntityMemory() {

	m_indexTable.push_back(std::unordered_map<becs::ComponentID, uint32_t>());
}

void MemoryManager::initComponentMemory(size_t compSize) {
	m_componentMemory.push_back(std::move(becs::ComponentMemory(compSize)));
	m_freeMemory.push_back(std::queue<uint32_t>());
}

void MemoryManager::addComponentInstance(becs::ComponentID compID, EntityID entID) {

	if (!m_freeMemory[compID].empty()) {
		m_indexTable[entID].insert(std::make_pair(compID, m_freeMemory[compID].front()));
		m_freeMemory[compID].pop();
		return;
	}

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

void becs::MemoryManager::freeAllCompMemFromEnt(EntityID entID, const std::vector<ComponentID>& compIDs) {

	for (const auto& compID : compIDs) {

		if (hasComponent(entID, compID)) {
			m_freeMemory[compID].push(m_indexTable[entID].at(compID));
			m_indexTable[entID].erase(compID);
		}
	}

	
}

size_t becs::MemoryManager::getCompMemoryAllocSize(ComponentID compID) {
	return m_componentMemory[compID].getAllocatedMemory();
}

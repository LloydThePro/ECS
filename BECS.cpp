#include "BECS.h"

#define _ENABLE_DEBUG
#ifdef _ENABLE_DEBUG

#include <iostream>
void becs::BECS::debug() {

	std::cout << "Entities Exist: " << m_entManager.getEntityCapacity() << "\tEntities Alive: " << m_entManager.getEntityCount() << '\n';

	std::cout << "Component resistered: " << m_compManager.getLastIndex() + 1 << '\n';

	std::cout << "Component Memory Locations: \n";
	m_memManager.debug();
	

}



#endif // _ENABLE_DEBUG




using namespace becs;



EntityID BECS::createEntity() {

	m_memManager.initEntityMemory();

	return m_entManager.registerEntity();

}


void BECS::destroyEntity(EntityID entID) {
	m_entManager.unregisterEntity(entID);
}
void BECS::destroyEntityAtBack() {

}
void BECS::destroyEntityAtFront() {

}

ComponentID BECS::registerComponent(size_t compSize) {
	
	m_memManager.initComponentMemory(compSize);
	return m_compManager.registerComponent();

}

void BECS::bindComponentToEnt(EntityID entID, ComponentID compID) {
	
	m_memManager.addComponentInstance(compID,entID);

}

FilterID becs::BECS::createFilter() {
	return m_filterManager.createFilter();
}

void becs::BECS::addComponentToFilter(FilterID id, ComponentID compID) {
	m_filterManager.addComponent(id, compID);
}

void becs::BECS::addEntToFilter(FilterID id, EntityID entID) {

	bool doesQualify = true;

	for (const auto& c : m_filterManager.getComponents(id)) {

		if (!m_memManager.hasComponent(entID, c)) {
			doesQualify = false;
			break;
		}
	}

	if (doesQualify) {
		m_filterManager.addEntToFilter(id, entID);
	}

}

void becs::BECS::updateFilterContent() {

	size_t n = m_entManager.getEntityCapacity();

	for (uint32_t i = 0; i < n; i++) {

		for (auto& filter : m_filterManager.getFilter()) {
			
			bool doesQualify = true;

			for (const auto& compID : filter.components) {

				if(m_entManager.doesExist(i))
					if (!m_memManager.hasComponent(i, compID)) {
						doesQualify = false;
						
						break;
					}

			}
		
			if (doesQualify) {
				filter.entities.push_back(i);
			}

		}


	}


}

size_t becs::BECS::getComponentsByFilter(FilterID id, QueryComponent* queryArry, size_t count) {

	
	const auto& compIDs = m_filterManager.getComponents(id);
	uint32_t index = 0;
	for (const EntityID& entID : m_filterManager.getEntities(id)) {

		for (const auto& compID : compIDs) { 

			if (index < count) {
				queryArry[index].component = m_memManager.getComponent(entID, compID);
				queryArry[index].compID = compID;
			}
			
			index++;
		}
	}
	return index;
}





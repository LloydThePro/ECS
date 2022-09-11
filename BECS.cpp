#include "BECS.h"




using namespace becs;



EntityID BECS::createEntity() {

	
	bool isRealloc;
	EntityID id = m_entManager.registerEntity(&isRealloc);
	if (!isRealloc) {
		m_memManager.initEntityMemory();
	}

	return id;

}


void BECS::destroyEntity(EntityID entID) {
	m_memManager.freeAllCompMemFromEnt(entID, m_entManager.getComponentBounded(entID));
	m_entManager.unregisterEntity(entID);
	m_filterManager.removeEntity(entID);
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
	m_memManager.addComponentInstance(compID, entID);
	m_entManager.bindComponentToEnt(entID, compID);
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

void becs::BECS::removeEntityToFilter(FilterID id, EntityID entID) {
	m_filterManager.removeEntity(id, entID);
}

void becs::BECS::removeEntityToFilter(EntityID entID) {
	m_filterManager.removeEntity(entID);
}

void becs::BECS::destroyFilter(FilterID fID) {

	m_filterManager.destroyFilter(fID);

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

/*
* Gets all the components spefied by a filter Object
* @param id - the filter ID which speficies the components that will be queried
* @param queryArry - the array structure that will contain the component pointer and a Component ID
* @param count - the max count of 'queryArry'
* @return - returns the componennt count it retrives. the return value may be bigger than the 'count'
*/
size_t becs::BECS::getComponentsByFilter(FilterID id, QueryData* queryArry, size_t count) {

	
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

bool becs::BECS::getSingleComponentByFilter(FilterID id, SingleQueryData* query, QueryIteration iter) {
	
	const auto& compIDs = m_filterManager.getComponents(id);
	const auto& entIDs = m_filterManager.getEntities(id);

	


	uint32_t tempStateEnt = query->entIdx;
	uint32_t tempStateComp = query->compIdx;
	size_t compIndex = compIDs.size();
	size_t entIndex = entIDs.size();
	
	

	if (query->compIdx >= compIDs.size() || query->entIdx >= entIDs.size()) {
		query->compIdx = tempStateComp;
		query->entIdx = tempStateEnt;
		return false;
	}
	ComponentID compID = compIDs[query->compIdx];
	query->component = m_memManager.getComponent(entIDs[query->entIdx], compID);
	query->compID = compID;
	
	switch (iter) {

	case becs::QueryIteration::NEXT_COMP:
		query->compIdx++;
		break;
	case becs::QueryIteration::PREV_COMP:
		if(query->compIdx > 0)
			query->compIdx--;
		break;
	case becs::QueryIteration::NEXT_ENT:
		query->entIdx++;
		break;
	case becs::QueryIteration::PREV_ENT:
		if (query->entIdx > 0)
			query->entIdx--;
		break;
	case becs::QueryIteration::LAST_COMP:
		query->compIdx = compIndex - 1;
		break;
	case becs::QueryIteration::LAST_ENT:
		query->entIdx = entIndex - 1;
		break;
	case becs::QueryIteration::FIRST_COMP:
		query->compIdx = 0;
		break;
	case becs::QueryIteration::FIRST_ENT:
		query->entIdx = 0;
		break;
	default:
		return false;
		break;
	}

	
	return true;
}

size_t becs::BECS::getCompMemSize(ComponentID compID) {
	return m_memManager.getCompMemoryAllocSize(compID);
}

size_t becs::BECS::getEntityCount(){
	return m_entManager.getEntityCount();
}

size_t becs::BECS::getEntityCapacity()
{
	return m_entManager.getEntityCapacity();
}





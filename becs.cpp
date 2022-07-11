#include "becs.h"

ComponentID BECS::registerComponent(unsigned int size) {
	m_registeredComp.push_back(m_compIDCounter);
	CompMemCell cell;
	m_freeCompMemory.push_back(std::move(std::vector<FreeMem>()));
	cell.m_compSize = size;
	m_compMemory.push_back(std::move(cell));
	ComponentID id = m_compIDCounter;
	m_compIDCounter++;
	return id;
}

ComponentID* BECS::getComponentBinded(EntityID entID, unsigned int * size)
{
	if (!(entID < m_entIDCounter))return nullptr;
	
	// check if this entity is deleted
	for (EntityID id : m_freeEntity) {
		if (id == entID)return nullptr;
	}
	*size = m_entity[entID].m_bindedComp.size();
	
	return m_entity[entID].m_bindedComp.data();
}


void BECS::addComponent(EntityID entID, ComponentID compID) {
	if (!(entID < m_entIDCounter))return;
	if (!(compID < m_compIDCounter))return;
	// need to check if in free space
	
	// check if this entity is deleted
	for (EntityID id : m_freeEntity) {
		if (id == entID)return;
	}
	
	// check if the componennt is already bound to the entity
	for (ComponentID& c : m_entity[entID].m_bindedComp) {
		if (c == compID)return;
	}

	

	MemCell cell;
	cell.m_comp = new char[m_compMemory[compID].m_compSize]; 
	cell.m_entOwner = entID;

	m_entity[entID].m_bindedComp.push_back(compID);
	

	m_compMemory[compID].m_components.push_back(std::move(cell));
	CompMemIndex index;

	index.index = m_compMemory[compID].m_components.size() - 1;
	index.id = compID;
	m_entity[entID].m_memIndex.push_back(index);

}

void BECS::removeComponent(EntityID entID, ComponentID compID){

	if (!(entID < m_entIDCounter))return;
	if (!(compID < m_compIDCounter))return;
	// need to check if in free space

	// check if this entity is deleted
	for (EntityID id : m_freeEntity) {
		if (id == entID)return;
	}

	// check if the componennt is already bound to the entity
	bool isCompontBound = true;
	for (ComponentID& c : m_entity[entID].m_bindedComp) {
		isCompontBound = c == compID;
	}

	if (!isCompontBound)return;


	if (m_entity[entID].m_bindedComp.empty())return;
	
	int index = 0;
	bool isFound = false;
	for (ComponentID& id : m_entity[entID].m_bindedComp) {
		
		if (id == compID) {
			isFound = true;
			break;
		}
		index++;
	}

	FreeMem mem;
	mem.id = compID;
	mem.index = 0;
	
	for (CompMemIndex& c : m_entity[entID].m_memIndex) {
		if (c.id == compID) {
			break;
		}
		mem.index++;
	}

	
	
	
	m_freeCompMemory[compID].push_back(std::move(mem));

	m_entity[entID].m_bindedComp.erase(m_entity[entID].m_bindedComp.begin() + index);

}

void BECS::destroyEntity(EntityID entID){
	if (!(entID < m_entIDCounter))return;
	
	// check if this entity is deleted
	for (EntityID id : m_freeEntity) {
		if (id == entID)return;
	}
	int count = m_entity[entID].m_bindedComp.size();

	for (int i = 0; i < count; i++) {
		removeComponent(entID, m_entity[entID].m_bindedComp[i]);
	}
	m_entity[entID].m_bindedComp.clear();
	m_entity[entID].m_memIndex.clear();
	m_entity.erase(m_entity.begin() + entID);
	m_freeEntity.push_back(entID);
}

EntityID BECS::createEntity()
{

	EntityID id = m_entIDCounter;
	m_entIDCounter++;
	Entity ent;
	ent.m_ID = id;
	m_entity.push_back(std::move(ent));
	return id;
}

QueryComponent BECS::getComponent(ComponentID compID)
{
	QueryComponent component;

	component.m_compArry = m_compMemory[compID].m_components.data();
	component.m_arryCount = m_compMemory[compID].m_components.size();
	component.m_compSize = m_compMemory[compID].m_compSize;
	component.m_ID = compID;
	return std::move(component);
}

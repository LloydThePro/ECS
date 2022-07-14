#include "becs.h"

ComponentID BECS::registerComponent(unsigned int size) {

	m_registeredComp.push_back(m_compIDCounter);
	CompMemCell cell;
	cell.m_compSize = size;
	m_compMemory.push_back(std::move(cell));
	m_freeCompMemory.push_back(std::move(std::queue<FreeMem>()));
	ComponentID id = m_compIDCounter;
	m_compIDCounter++;
	return id;
}

ComponentID* BECS::getComponentBinded(EntityID entID, unsigned int * size)
{
	if (!(entID < m_entIDCounter))return nullptr;
	
	// check if this entity is deleted
	auto isValid = m_entity.find(entID);
	if (isValid == m_entity.end())return nullptr;

	*size = m_entity[entID].m_bindedComp.size();
	
	return m_entity[entID].m_bindedComp.data();
}


void BECS::addComponent(EntityID entID, ComponentID compID) {
	if (!(entID < m_entIDCounter))return;
	if (!(compID < m_compIDCounter))return;
	
	
	// check if this entity is deleted
	auto isValid = m_entity.find(entID);
	if (isValid == m_entity.end())return;
	
	// check if the componennt is already bound to the entity
	for (ComponentID& c : m_entity[entID].m_bindedComp) {
		if (c == compID)return;
	}

	if (!m_freeCompMemory[compID].empty()) {
		CompMemIndex temp;
		m_entity[entID].m_bindedComp.push_back(compID);
		FreeMem mem = m_freeCompMemory[compID].front();
		m_freeCompMemory[compID].pop();
		temp.id = mem.id;
		temp.index = mem.index;
		m_entity[entID].m_memIndex.insert(std::make_pair(compID, temp));
		m_compMemory[compID].m_components[mem.compMemIndex].isValid = true;
		return;
		/*for (FreeMem mem : m_freeCompMemory) {
			if (mem.id == compID) {

				m_entity[entID].m_bindedComp.push_back(compID);
				CompMemIndex temp;
				temp.id = mem.id;
				temp.index = mem.index;
				
				return;
			}

		}*/


	}
	

	MemCell cell;
	cell.m_comp = new char[m_compMemory[compID].m_compSize]; 
	cell.m_entOwner = entID;
	cell.isValid = true;

	m_entity[entID].m_bindedComp.push_back(compID);
	

	m_compMemory[compID].m_components.push_back(std::move(cell));
	CompMemIndex index;

	index.index = m_compMemory[compID].m_components.size() - 1;
	index.id = compID;
	m_entity[entID].m_memIndex.insert(std::make_pair(compID, index));

}

void BECS::removeComponent(EntityID entID, ComponentID compID){

	if (!(entID < m_entIDCounter))return;
	if (!(compID < m_compIDCounter))return;
	// need to check if in free space

	auto isValid = m_entity.find(entID);
	if (isValid == m_entity.end())return;

	int index = 0;
	bool isCompontBound = false;
	for (ComponentID& c : m_entity[entID].m_bindedComp) {
		
		if (c == compID) {
			isCompontBound = true;
			break;
		}
		index++;
	}

	if (!isCompontBound)return;


	if (m_entity[entID].m_bindedComp.empty())return;
	
	
	/*bool isFound = false;
	for (ComponentID& id : m_entity[entID].m_bindedComp) {
		
		if (id == compID) {
			isFound = true;
			break;
		}
		index++;
	}*/

	FreeMem mem;
	mem.id = compID;
	mem.index = 0;	// index to the memory indexes of an entity
	
	
	/*for (CompMemIndex& c : m_entity[entID].m_memIndex) {
		if (c.id == compID) {
			mem.compMemIndex = c.index;
			break;
		}
		mem.index++;
	}*/

	mem.compMemIndex = m_entity[entID].m_memIndex[compID].index;

	m_compMemory[compID].m_components[mem.compMemIndex].isValid = false;
	//m_entity[entID].m_memIndex.erase(m_entity[entID].m_memIndex.begin() + mem.index);
	m_entity[entID].m_memIndex.erase(compID);
	
	
	//m_freeCompMemory.insert(std::make_pair(compID, std::move(mem)));
	m_freeCompMemory[compID].push(std::move(mem));

	m_entity[entID].m_bindedComp.erase(m_entity[entID].m_bindedComp.begin() + index);

}

void BECS::destroyEntity(EntityID entID){
	if (!(entID < m_entIDCounter))return;
	
	// check if this entity is deleted
	auto isValid = m_entity.find(entID);

	if (isValid == m_entity.end())return;


	
	auto& entRef = m_entity[entID].m_bindedComp;
	
	for (auto comp : entRef) {
		removeComponent(entID, comp);
	}

	


	m_entity[entID].m_bindedComp.clear();
	m_entity[entID].m_memIndex.clear();
	m_entity.erase(entID);
	m_freeEntity.push(entID);
}

EntityID BECS::createEntity()
{

	if (!m_freeEntity.empty()) {

		EntityID id = m_freeEntity.front();
		m_freeEntity.pop();
		return id;
	}

	EntityID id = m_entIDCounter;
	m_entIDCounter++;
	Entity ent;
	ent.m_ID = id;
	m_entity.insert(std::make_pair(id, std::move(ent)));

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


BECS::~BECS() {

	for (CompMemCell& cell : m_compMemory) {
		for (MemCell& memcell : cell.m_components) {
			delete[] memcell.m_comp;
		}
		cell.m_components.clear();
	}
	m_registeredComp.clear();
	m_compMemory.clear();
	m_freeCompMemory.clear();
	m_entity.clear();
}

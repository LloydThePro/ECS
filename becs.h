#pragma once
#include "types.h"

class BECS
{
public:

	ComponentID				registerComponent(unsigned int size);
	ComponentID*			getComponentBinded(EntityID entID, unsigned int* size);
	void					addComponent(EntityID entID, ComponentID compID);
	void					removeComponent(EntityID entID, ComponentID compID);
	void					destroyEntity(EntityID id);
	EntityID				createEntity();
	QueryComponent			getComponent(ComponentID);

private:
	EntityID								m_entIDCounter;
	ComponentID								m_compIDCounter;
	std::vector<ComponentID>				m_registeredComp;
	std::vector<CompMemCell>				m_compMemory;
	std::vector<std::vector<FreeMem>>		m_freeCompMemory;
	std::vector<Entity>						m_entity;
	std::vector<EntityID>					m_freeEntity;
};


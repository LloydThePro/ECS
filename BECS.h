#pragma once



#include "MemoryManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "ComponentFilterManager.h"
namespace becs{


	class BECS {

	public:

		EntityID createEntity();
		void destroyEntity(EntityID entID);
		void destroyEntityAtBack();
		void destroyEntityAtFront();

		ComponentID registerComponent(size_t compSize);
		
		void bindComponentToEnt(EntityID entID, ComponentID compID);

		FilterID createFilter();
		void addComponentToFilter(FilterID id, ComponentID compID);
		void addEntToFilter(FilterID id, EntityID entID);
		void removeEntityToFilter(FilterID id, EntityID entID);
		void removeEntityToFilter(EntityID entID);
		void destroyFilter(FilterID fID);
		void updateFilterContent();
		size_t getComponentsByFilter(FilterID id, QueryData* queryArry, size_t count);
		bool getSingleComponentByFilter(FilterID id, SingleQueryData* query, QueryIteration iter);
		size_t getCompMemSize(ComponentID compID);
		size_t getEntityCount();
		size_t getEntityCapacity();


	private:
		ComponentManager				m_compManager;
		EntityManager					m_entManager;
		MemoryManager					m_memManager;
		ComponentFilterManager			m_filterManager;


	};



}



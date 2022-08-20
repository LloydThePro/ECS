#pragma once

#ifdef _DEBUG_MODE_ENABLED
#define _ENABLE_DEBUG
#endif


#define _ENABLE_DEBUG
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
		void updateFilterContent();
		size_t getComponentsByFilter(FilterID id, QueryComponent* queryArry, size_t count);

#ifdef _ENABLE_DEBUG
		void debug();
#endif // _ENABLE_DEBUG




	private:
		ComponentManager				m_compManager;
		EntityManager					m_entManager;
		MemoryManager					m_memManager;
		ComponentFilterManager			m_filterManager;


	};



}



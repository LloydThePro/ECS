#pragma once
#include "Types.h"
#include <vector>

namespace becs {



	class ComponentFilterManager {
	public:

		FilterID createFilter();

		void addComponent(FilterID filterID, ComponentID compID);
		void addComponent(FilterID filterID, ComponentID* compIDs, size_t count);
		const std::vector<EntityID>& getEntities(FilterID filterID);
		const std::vector<ComponentID>& getComponents(FilterID filterID);
		
		std::vector<Filter>& getFilter();
		void addEntities(FilterID id, EntityID entID);
		void copyFilter(FilterID to, FilterID from);
		void addEntToFilter(FilterID id, EntityID entID);


	private:
		
		std::vector<Filter> m_filters;
		

	};






}


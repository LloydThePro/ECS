#pragma once
#include <cstdint>
#include <vector>
namespace becs {

	typedef uint32_t EntityID;
	typedef uint32_t ComponentID;
	typedef uint32_t FilterID;


	struct Entity {
		std::vector<ComponentID> bindedComponents;
		EntityID entID;
	};

	typedef struct {
		std::vector<ComponentID> components; // componentns to be filtered
		std::vector<EntityID> entities;		// entities that has those component requirement
	}Filter;


	typedef struct {
		void* component;
		ComponentID compID;
	}QueryComponent;

}

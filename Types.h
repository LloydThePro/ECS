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
	}QueryData;


	typedef struct {
		void* component;
		ComponentID compID;
		uint32_t entIdx;
		uint32_t compIdx;
	}SingleQueryData;

	enum class QueryIteration{
		NEXT_COMP, PREV_COMP, NEXT_ENT, PREV_ENT, LAST_ENT, LAST_COMP, FIRST_COMP, FIRST_ENT
	};
}
